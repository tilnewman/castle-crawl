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
#include "popup-manager.hpp"
#include "resources.hpp"
#include "settings.hpp"
#include "state-machine.hpp"

#include <iostream>

namespace castlecrawl
{

    StatePlay::StatePlay(Context & context)
        : StateBase(State::Play)
        , m_fps()
        , m_windowOutline()
    {
        m_windowOutline.setPosition(1.0f, 1.0f);
        m_windowOutline.setSize(context.layout.windowSize() - sf::Vector2f{ 2.0f, 2.0f });
        m_windowOutline.setFillColor(context.config.background_color);
        m_windowOutline.setOutlineThickness(1.0f);
        m_windowOutline.setOutlineColor(sf::Color(80, 80, 80));

        m_fps.reset(context);
    }

    void StatePlay::update(Context & context, const float frameTimeSec)
    {
        context.anim.update(frameTimeSec);
        m_fps.update();
    }

    void StatePlay::handleEvent(Context & context, const sf::Event & event)
    {
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
        target.draw(m_windowOutline, states);
        context.map().draw(context, target, states);
        target.draw(context.board, states);
        target.draw(context.anim, states);
        target.draw(m_fps, states);
    }

} // namespace castlecrawl
