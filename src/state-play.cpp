// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-play.cpp
//
#include "state-play.hpp"

#include "animation-player.hpp"
#include "board.hpp"
#include "context.hpp"
#include "item-factory.hpp"
#include "keys.hpp"
#include "map.hpp"
#include "maps.hpp"
#include "media.hpp"
#include "music-player.hpp"
#include "player.hpp"
#include "popup-manager.hpp"
#include "process.hpp"
#include "settings.hpp"
#include "state-direction.hpp"
#include "state-machine.hpp"
#include "state-treasure.hpp"
#include "util.hpp"

#include <iostream>

namespace castlecrawl
{

    StatePlay::StatePlay(Context & context)
        : StateBase(State::Play)
        , m_fps()
        , m_bgRectangle()
    {
        m_bgRectangle.setPosition(0.0f, 0.0f);
        m_bgRectangle.setSize(context.layout.windowSize());
        m_bgRectangle.setFillColor(context.config.background_color);
        m_bgRectangle.setOutlineThickness(0.0f);

        m_fps.reset(context);
    }

    void StatePlay::onEnter(Context & context)
    {
        if ((Action::Fight == context.process.action) && StateDirection::isClosingEventValid())
        {
            const MapPos_t fightPos = keys::moveIfDir(
                context.board.player().position(), StateDirection::m_closingEvent.key.code);

            const char fightChar = context.maps.get().getChar(fightPos);

            if (fightChar == tileImageChar(TileImage::Empty))
            {
                context.audio.play("miss.ogg");
            }
            else if (fightChar == tileImageChar(TileImage::Barrel))
            {
                context.audio.play("barrel-break.ogg");

                context.maps.get().setChar(fightPos, ' ');
                context.maps.reloadAfterChange(context);

                using namespace item;
                StateTreasure::treasure = context.items.randomTreasureFind(context);

                context.state.setChangePending(State::Treasure);
            }
            else
            {
                context.audio.play("hit.ogg");
            }

            StateDirection::m_closingEvent = {};
            context.process.action = Action::None;

            return;
        }
    }

    void StatePlay::update(Context & context, const float frameTimeSec)
    {
        context.anim.update(frameTimeSec);
        context.board.update(context, frameTimeSec);
        m_fps.update();
        updateReplenish(context, frameTimeSec);
    }

    void StatePlay::updateReplenish(Context & context, const float frameTimeSec)
    {
        m_replenishTimerSec -= frameTimeSec;
        if (m_replenishTimerSec < 0.0f)
        {
            m_replenishTimerSec = m_replenishIntervalSec;
            context.player.health().adjCurrent(1);
            context.player.mana().adjCurrent(1);
        }
    }

    void StatePlay::handleEvent(Context & context, const sf::Event & event)
    {
        if (sf::Event::MouseButtonPressed == event.type)
        {
            const sf::Vector2f mousePosition = sf::Vector2f{ sf::Mouse::getPosition() };
            const MapPos_t mapPosition = context.layout.cellPosition(mousePosition);
            if (context.layout.isPositionValid(mapPosition))
            {
                std::string message{ "The map char at " };
                message += std::to_string(mapPosition.x);
                message += ',';
                message += std::to_string(mapPosition.y);
                message += " is '";
                message += context.maps.get().getChar(mapPosition);
                message += "'";
                context.popup.setup(context, message);
                context.state.setChangePending(State::Popup, State::Play);
                return;
            }
        }

        // all that remain are keystrokes
        if (sf::Event::KeyPressed != event.type)
        {
            return;
        }

        if ((sf::Keyboard::Escape == event.key.code) || (sf::Keyboard::Q == event.key.code))
        {
            std::cout << "Player pressed 'Q' or 'Escape'.  Quitting." << std::endl;
            context.state.setChangePending(State::Quit);
            return;
        }

        if (sf::Keyboard::Space == event.key.code)
        {
            context.state.setChangePending(State::Pause, State::Play);
            return;
        }

        // TEMP TODO REMOVE after testing
        if (sf::Keyboard::P == event.key.code)
        {
            context.popup.setup(context, "All your bases are belong to us.");
            context.state.setChangePending(State::Popup, State::Play);
            return;
        }

        if (sf::Keyboard::F == event.key.code)
        {
            context.process.action = Action::Fight;
            context.state.setChangePending(State::Direction, State::Play);
            return;
        }

        if (sf::Keyboard::I == event.key.code)
        {
            context.state.setChangePending(State::Inventory);
            return;
        }

        // everything else is handling arrow keys
        if (!keys::isArrow(event.key.code))
        {
            return;
        }

        const MapPos_t oldPos = context.board.player().position();
        const Pieces oldPiece = context.board.whichAt(oldPos);
        const MapPos_t newPos = keys::moveIfDir(oldPos, event.key.code);
        const Pieces newPiece = context.board.whichAt(newPos);

        // leave the map cases
        for (const MapLink & link : context.maps.get().links())
        {
            if (link.from_pos == newPos)
            {
                if ((oldPiece == Pieces::StairsUp) || (oldPiece == Pieces::StairsDown))
                {
                    context.audio.play("stairs.ogg");
                }

                context.maps.switchTo(context, link);
                return;
            }
        }

        // obstacle bump cases
        if (isPieceObstacle(newPiece))
        {
            if (newPiece == Pieces::Lava)
            {
                context.audio.play("burn.ogg");
            }
            else if (newPiece == Pieces::Water)
            {
                context.audio.play("splash.ogg");
            }
            else if (newPiece == Pieces::DoorLocked)
            {
                context.audio.play("locked.ogg");
            }
            else
            {
                context.audio.play("tap-wood-low.ogg");
            }

            return;
        }

        context.board.player().move(context, event.key.code);

        if (newPiece == Pieces::None)
        {
            context.audio.play("tick-on-2.ogg");
        }
        else if (newPiece == Pieces::DoorUnlocked)
        {
            context.audio.play("door-open.ogg");
        }

        const std::size_t lavaAroundCount = context.maps.get().countCharsAround(newPos, 'l');
        if (lavaAroundCount == 0)
        {
            context.music.stop("lava.ogg");
        }
        else
        {
            context.music.start("lava.ogg");
        }

        const std::size_t waterAroundCount = context.maps.get().countCharsAround(newPos, 'w');
        if (waterAroundCount == 0)
        {
            context.music.stop("water-bubbles.ogg");
        }
        else
        {
            context.music.start("water-bubbles.ogg");
        }
    }

    void StatePlay::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_bgRectangle, states);
        context.maps.drawCurrentLower(context, target, states);
        target.draw(context.board, states);
        context.maps.drawCurrentUpper(context, target, states);
        target.draw(context.anim, states);
        target.draw(m_fps, states);
    }

} // namespace castlecrawl
