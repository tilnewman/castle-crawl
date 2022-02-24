// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-edit.cpp
//
#include "state-edit.hpp"

#include "board.hpp"
#include "context.hpp"
#include "map.hpp"
#include "popup-manager.hpp"
#include "resources.hpp"
#include "settings.hpp"
#include "state-machine.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>

namespace mapper
{

    StateEdit::StateEdit(Context & context)
        : StateBase(State::Edit)
        , m_fps()
        , m_windowOutline()
    {
        m_windowOutline.setPosition(1.0f, 1.0f);
        m_windowOutline.setSize(context.layout.windowSize() - sf::Vector2f{ 2.0f, 2.0f });
        m_windowOutline.setFillColor(sf::Color::Transparent);
        m_windowOutline.setOutlineThickness(1.0f);
        m_windowOutline.setOutlineColor(sf::Color(80, 80, 80));

        m_fps.reset(context);
    }

    void StateEdit::update(Context &, const float) { m_fps.update(); }

    void StateEdit::handleEvent(Context & context, const sf::Event & event)
    {
        // all that remain are keystrokes
        if (sf::Event::KeyPressed != event.type)
        {
            return;
        }

        if ((sf::Keyboard::Escape == event.key.code) || (sf::Keyboard::Q == event.key.code))
        {
            std::cout << "Player pressed 'Q' or 'Escape'.  Quitting." << std::endl;
            context.state.setChangePending(State::Teardown);
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

    void StateEdit::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.clear(context.config.background_color);
        // context.map().draw(context, target, states);
        target.draw(context.board, states);
        target.draw(m_windowOutline, states);
        target.draw(m_fps, states);
    }

} // namespace mapper
