// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-play.cpp
//
#include "state-play.hpp"

#include "animation-player.hpp"
#include "board.hpp"
#include "context.hpp"
#include "map.hpp"
#include "maps.hpp"
#include "popup-manager.hpp"
#include "resources.hpp"
#include "settings.hpp"
#include "state-machine.hpp"
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

    void StatePlay::update(Context & context, const float frameTimeSec)
    {
        context.anim.update(frameTimeSec);
        context.board.update(context, frameTimeSec);
        m_fps.update();
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
                context.state.setChangePending(State::Popup);
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
            context.state.setChangePending(State::Pause);
            return;
        }

        // TEMP TODO REMOVE after testing
        if (sf::Keyboard::P == event.key.code)
        {
            context.popup.setup(context, "All your bases are belong to us.");
            context.state.setChangePending(State::Popup);
            return;
        }

        context.board.player.handleEvent(context, event);
    }

    void StatePlay::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_bgRectangle, states);
        context.maps.drawCurrent(context, target, states);
        target.draw(context.board, states);
        target.draw(context.anim, states);
        target.draw(m_fps, states);
    }

} // namespace castlecrawl
