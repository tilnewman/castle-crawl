// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-play.cpp
//
#include "state-play.hpp"

#include "animation-player.hpp"
#include "board.hpp"
#include "config.hpp"
#include "context.hpp"
#include "item-factory.hpp"
#include "keys.hpp"
#include "layout.hpp"
#include "map.hpp"
#include "maps.hpp"
#include "media.hpp"
#include "music-player.hpp"
#include "player.hpp"
#include "popup-manager.hpp"
#include "process.hpp"
#include "save-game.hpp"
#include "sound-player.hpp"
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
        , m_topPanel()
        , m_splatTimerSec(0.0f)
        , m_splatSprite()
    {
        m_bgRectangle.setPosition(0.0f, 0.0f);
        m_bgRectangle.setSize(context.layout.windowSize());
        m_bgRectangle.setFillColor(context.config.background_color);
        m_bgRectangle.setOutlineThickness(0.0f);

        m_fps.reset(context);

        m_topPanel.setup(context);
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
            else if (
                (fightChar == tileImageChar(TileImage::Plant1)) ||
                (fightChar == tileImageChar(TileImage::Plant2)) ||
                (fightChar == tileImageChar(TileImage::Plant3)) ||
                (fightChar == tileImageChar(TileImage::Plant4)))
            {
                context.audio.play("chop.ogg");

                context.maps.get().setChar(fightPos, ' ');
                context.maps.reloadAfterChange(context);

                using namespace item;
                StateTreasure::treasure = context.items.randomHerbFind(context);

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
        m_topPanel.update(context, frameTimeSec);
        context.anim.update(frameTimeSec);
        context.board.update(context, frameTimeSec);
        m_fps.update();
        updateReplenish(context, frameTimeSec);
        updateSplat(frameTimeSec);
    }

    void StatePlay::updateSplat(const float frameTimeSec)
    {
        m_splatTimerSec -= frameTimeSec;
        if (m_splatTimerSec < 0.0f)
        {
            m_splatTimerSec = 0.0f;
            m_splatSprite = sf::Sprite();
        }
    }

    void StatePlay::updateReplenish(Context & context, const float frameTimeSec)
    {
        m_replenishTimerSec -= frameTimeSec;
        if (m_replenishTimerSec < 0.0f)
        {
            m_replenishTimerSec = m_replenishIntervalSec;

            context.player.health().adjCurrentNormalClamped(1);
            context.player.mana().adjCurrentNormalClamped(1);
        }
    }

    void StatePlay::handleEvent(Context & context, const sf::Event & event)
    {
        // all that remain are keystrokes
        if (sf::Event::KeyPressed != event.type)
        {
            return;
        }

        // TODO TEMP remove after dev
        if ((sf::Keyboard::Escape == event.key.code) || (sf::Keyboard::Q == event.key.code))
        {
            std::cout << "Player pressed 'Q' or 'Escape'.  Quitting." << std::endl;
            context.state.setChangePending(State::Quit);
            return;
        }

        // TODO TEMP remove after testing
        if (sf::Keyboard::P == event.key.code)
        {
            context.popup.setupPaper(
                context,
                PopupBackground::Paper1,
                FontSize::Small,
                sf::Color::Black,
                "You wake up in an ancient but somehow still sturdy looking cell.  The cold and "
                "hunger hurt, but the stinging lump on your head was what woke you.  It's the only "
                "gift given by the guards.  They took "
                "everything else, except your clothes. <paragraph> In the distance you can hear "
                "the cries "
                "and moans of other prisoners.  Your gut drops at the thought of being one of "
                "them.  Fearsome stories of this castle prison are know wide and far.");

            context.state.setChangePending(State::Popup, State::Play);
            return;
        }

        // TODO TEMP remove after testing
        if (sf::Keyboard::M == event.key.code)
        {
            m_splatTimerSec = 1.0f;

            const std::size_t splatImageIndex{ context.random.fromTo(
                0_st, static_cast<std::size_t>(SplatImage::Count) - 1_st) };

            m_splatSprite = context.media.splatSprite(static_cast<SplatImage>(splatImageIndex));

            const sf::FloatRect playerRect{ context.layout.cellBounds(
                context.board.player().position()) };

            util::fitAndCenterInside(m_splatSprite, playerRect);

            context.board.player().shakeStart();
            return;
        }

        // save game
        if (sf::Keyboard::S == event.key.code)
        {
            context.save.saveToFile(context);
            context.popup.setupBanner(context, "Game Saved");
            context.state.setChangePending(State::Popup, State::Play);
            return;
        }

        // load game
        if (sf::Keyboard::L == event.key.code)
        {
            const std::string loadResult{ context.save.loadFromFile(context) };
            context.popup.setupBanner(context, ((loadResult.empty()) ? "Game Loaded" : loadResult));
            context.state.setChangePending(State::Popup, State::Play);
            return;
        }

        // pause
        if (sf::Keyboard::Space == event.key.code)
        {
            context.state.setChangePending(State::Pause, State::Play);
            return;
        }

        // fight
        if (sf::Keyboard::F == event.key.code)
        {
            context.process.action = Action::Fight;
            context.state.setChangePending(State::Direction, State::Play);
            return;
        }

        // inventory
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
        context.maps.drawLower(context, target, states);
        target.draw(context.board, states);
        context.maps.drawUpper(context, target, states);
        target.draw(m_topPanel, states);
        target.draw(context.anim, states);
        target.draw(m_fps, states);
        target.draw(m_splatSprite, states);
    }

} // namespace castlecrawl
