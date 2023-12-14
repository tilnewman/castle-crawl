// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-edit.cpp
//
#include "state/state-edit.hpp"

#include "audio/sound-player.hpp"
#include "display/layout.hpp"
#include "display/media.hpp"
#include "display/popup-manager.hpp"
#include "map/board.hpp"
#include "map/map.hpp"
#include "misc/context.hpp"
#include "misc/sfml-util.hpp"
#include "state/editor.hpp"
#include "state/state-machine.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>

namespace castlecrawl
{

    StateEdit::StateEdit(Context &)
        : StateBase(State::Edit)
        , m_windowOutline()
    {}

    void StateEdit::onEnter(Context & context)
    {
        const std::filesystem::path filePath = m_editor.getFirstAvailableFilePath();
        m_editor.setFilename(filePath.filename().string());
        m_editor.setup(context);

        m_windowOutline.setPosition(util::position(context.layout.boardBounds()));
        m_windowOutline.setSize(util::size(context.layout.boardBounds()));
        m_windowOutline.setFillColor(sf::Color::Transparent);
        m_windowOutline.setOutlineThickness(1.0f);
        m_windowOutline.setOutlineColor(sf::Color(80, 80, 80));
    }

    void StateEdit::update(Context &, const float) { m_editor.updateFadeText(); }

    void StateEdit::handleEvent(Context & context, const sf::Event & event)
    {
        if (sf::Event::MouseButtonPressed == event.type)
        {
            m_editor.startDragging(
                context,
                { static_cast<float>(event.mouseButton.x),
                  static_cast<float>(event.mouseButton.y) });

            return;
        }

        if (sf::Event::MouseButtonReleased == event.type)
        {
            m_editor.stopDragging(
                context,
                { static_cast<float>(event.mouseButton.x),
                  static_cast<float>(event.mouseButton.y) });

            return;
        }

        if (m_editor.isDragging() && (sf::Event::MouseMoved == event.type))
        {
            m_editor.updateDragging(
                context,
                { static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) });

            return;
        }

        if ((sf::Event::KeyPressed == event.type) && (sf::Keyboard::H == event.key.code))
        {
            m_editor.showHelpText(context);
            return;
        }
        else if ((sf::Event::KeyReleased == event.type) && (sf::Keyboard::H == event.key.code))
        {
            m_editor.hideHelpText();
            return;
        }

        // all that remain are KeyPressed keystrokes
        if (sf::Event::KeyPressed != event.type)
        {
            return;
        }

        if (sf::Keyboard::Escape == event.key.code)
        {
            context.state.setChangePending(State::Quit);
            return;
        }

        if (event.key.control && (sf::Keyboard::R == event.key.code))
        {
            m_editor.reset(context);
            m_editor.startFadeText(context, "Reset Map");
            return;
        }

        if (sf::Keyboard::F == event.key.code)
        {
            m_editor.changeFloor(context);
            return;
        }

        if (sf::Keyboard::Up == event.key.code)
        {
            if (m_editor.position().y > 0)
            {
                m_editor.movePosition(context, { 0, -1 });
            }

            return;
        }

        if (sf::Keyboard::Down == event.key.code)
        {
            if (m_editor.position().y < (context.layout.cellCountsMax().y - 1))
            {
                m_editor.movePosition(context, { 0, 1 });
            }

            return;
        }

        if (sf::Keyboard::Left == event.key.code)
        {
            if (m_editor.position().x > 0)
            {
                m_editor.movePosition(context, { -1, 0 });
            }

            return;
        }

        if (sf::Keyboard::Right == event.key.code)
        {
            if (m_editor.position().x < (context.layout.cellCountsMax().x - 1))
            {
                m_editor.movePosition(context, { 1, 0 });
            }

            return;
        }

        // clang-format off
        if      (sf::Keyboard::Space == event.key.code) { m_editor.setCell(context, ' '); }
        else if (sf::Keyboard::L == event.key.code)     { m_editor.setCell(context, 'l'); }
        else if (sf::Keyboard::B == event.key.code)     { m_editor.setCell(context, 'b'); }
        else if (sf::Keyboard::W == event.key.code)     { m_editor.setCell(context, 'w'); }
        else if (sf::Keyboard::C == event.key.code)     { m_editor.setCell(context, 'c'); }
        else if (sf::Keyboard::K == event.key.code)     { m_editor.setCell(context, 'k'); }
        else if (sf::Keyboard::R == event.key.code)     { m_editor.setCell(context, 'r'); }
        else if (sf::Keyboard::A == event.key.code)     { m_editor.setCell(context, 'a'); }
        // clang-format on

        if ((sf::Keyboard::Period == event.key.code) || (sf::Keyboard::Delete == event.key.code) ||
            (sf::Keyboard::BackSpace == event.key.code))
        {
            m_editor.setCell(context, '.');
            return;
        }

        if (event.key.shift)
        {
            // clang-format off
            if      (sf::Keyboard::Num2 == event.key.code) { m_editor.setCell(context, '@'); }
            else if (sf::Keyboard::Num3 == event.key.code) { m_editor.setCell(context, '#'); }
            else if (sf::Keyboard::Num4 == event.key.code) { m_editor.setCell(context, '$'); }
            else if (sf::Keyboard::Num5 == event.key.code) { m_editor.setCell(context, '%'); }
            // clang-format on
        }

        if (sf::Keyboard::D == event.key.code)
        {
            if (event.key.shift)
            {
                m_editor.setCell(context, 'D');
            }
            else
            {
                m_editor.setCell(context, 'd');
            }

            return;
        }

        if (sf::Keyboard::S == event.key.code)
        {
            if (event.key.control)
            {
                m_editor.save(context);
                m_editor.startFadeText(context, "Saving...");
            }
            else if (event.key.shift)
            {
                m_editor.setCell(context, 'S');
            }
            else
            {
                m_editor.setCell(context, 's');
            }

            return;
        }
    }

    void StateEdit::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        m_editor.drawLower(context, target, states);
        target.draw(context.board, states);
        m_editor.drawUpper(context, target, states);
        target.draw(m_windowOutline, states);
    }

} // namespace castlecrawl
