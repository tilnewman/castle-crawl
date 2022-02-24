// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-edit.cpp
//
#include "state-edit.hpp"

#include "board.hpp"
#include "context.hpp"
#include "editor.hpp"
#include "map.hpp"
#include "popup-manager.hpp"
#include "resources.hpp"
#include "settings.hpp"
#include "state-machine.hpp"
#include "util.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>

namespace mapper
{

    StateEdit::StateEdit(Context &)
        : StateBase(State::Edit)
        , m_fps()
        , m_windowOutline()
    {}

    void StateEdit::onEnter(Context & context)
    {
        m_fps.reset(context);

        m_windowOutline.setPosition(util::position(context.layout.boardBounds()));
        m_windowOutline.setSize(util::size(context.layout.boardBounds()));
        m_windowOutline.setFillColor(sf::Color::Transparent);
        m_windowOutline.setOutlineThickness(1.0f);
        m_windowOutline.setOutlineColor(sf::Color(80, 80, 80));
    }

    void StateEdit::update(Context &, const float) { m_fps.update(); }

    void StateEdit::handleEvent(Context & context, const sf::Event & event)
    {
        // all that remain are keystrokes
        if (sf::Event::KeyPressed != event.type)
        {
            return;
        }

        if (sf::Keyboard::Escape == event.key.code)
        {
            context.state.setChangePending(State::Teardown);
            return;
        }

        if (event.key.control && (sf::Keyboard::R == event.key.code))
        {
            context.editor.reset(context);
        }

        if (sf::Keyboard::Up == event.key.code)
        {
            if (context.editor.position().y > 0)
            {
                context.editor.movePosition({ 0, -1 });
            }

            return;
        }

        if (sf::Keyboard::Down == event.key.code)
        {
            if (context.editor.position().y < (context.layout.cellCountsMax().y - 1))
            {
                context.editor.movePosition({ 0, 1 });
            }

            return;
        }

        if (sf::Keyboard::Left == event.key.code)
        {
            if (context.editor.position().x > 0)
            {
                context.editor.movePosition({ -1, 0 });
            }

            return;
        }

        if (sf::Keyboard::Right == event.key.code)
        {
            if (context.editor.position().x < (context.layout.cellCountsMax().x - 1))
            {
                context.editor.movePosition({ 1, 0 });
            }

            return;
        }

        // clang-format off
        if      (sf::Keyboard::Space == event.key.code) context.editor.setCell(context, ' ');
        else if (sf::Keyboard::L == event.key.code)     context.editor.setCell(context, 'l');
        else if (sf::Keyboard::B == event.key.code)     context.editor.setCell(context, 'b');
        else if (sf::Keyboard::W == event.key.code)     context.editor.setCell(context, 'w');
        else if (sf::Keyboard::C == event.key.code)     context.editor.setCell(context, 'c');
        // clang-format on

        if ((sf::Keyboard::Period == event.key.code) || (sf::Keyboard::Delete == event.key.code) ||
            (sf::Keyboard::BackSpace == event.key.code))
        {
            context.editor.setCell(context, '.');
        }

        if (sf::Keyboard::D == event.key.code)
        {
            if (event.key.shift)
            {
                context.editor.setCell(context, 'D');
            }
            else
            {
                context.editor.setCell(context, 'd');
            }
        }

        if (sf::Keyboard::S == event.key.code)
        {
            if (event.key.shift)
            {
                context.editor.setCell(context, 'S');
            }
            else
            {
                context.editor.setCell(context, 's');
            }
        }

        if (sf::Keyboard::F == event.key.code)
        {
            context.editor.setFloorIsStone(context, !context.editor.getFloorIsStone());
        }

        if (sf::Keyboard::F2 == event.key.code)
        {
            context.editor.save(context);
        }

        if (sf::Keyboard::F1 == event.key.code)
        {
            // clang-format off
            std::cout << 
                "----------------------------------\n"
                "  Escape    - Quit the map editor.\n"
                "  F1        - See this help text.\n"
                "  F2        - Save the map.\n"
                "  Spacebar  - Bare Floor\n"
                "  Delete    - Clear Cell\n"
                "  Period    - (same as Delete)\n"
                "  L         - Lava\n"
                "  W         - Water\n"
                "  d         - Door\n"
                "  D         - Locked Door\n"
                "  s         - Stairway Down\n"
                "  S         - Stairway Up\n"
                "  b         - Barrel\n"
                "  c         - Coffin\n"
                "  f         - Stone or Wood Floor\n"
                "  CNTRL-R   - ERASE EVERYTHING!\n"
                "----------------------------------\n"
                << std::endl;
            // clang-format on
        }
    }

    void StateEdit::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        context.editor.draw(context, target, states);
        target.draw(context.board, states);
        target.draw(m_windowOutline, states);
        target.draw(m_fps, states);
    }

} // namespace mapper
