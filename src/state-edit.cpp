// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-edit.cpp
//
#include "state-edit.hpp"

#include "board.hpp"
#include "context.hpp"
#include "editor.hpp"
#include "layout.hpp"
#include "map.hpp"
#include "media.hpp"
#include "popup-manager.hpp"
#include "sound-player.hpp"
#include "state-machine.hpp"
#include "util.hpp"

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

    void StateEdit::handleEvent(Context & context, const sf::Event & event)
    {
        if (sf::Event::MouseButtonPressed == event.type)
        {
            const sf::Vector2f mousePosition = sf::Vector2f{ sf::Mouse::getPosition() };
            const MapPos_t cellIndex = context.layout.cellPosition(mousePosition);
            if (context.layout.isPositionValid(cellIndex))
            {
                context.audio.play("thock-2");
                m_editor.setPosition(context, cellIndex);
            }

            return;
        }

        // all that remain are keystrokes
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
        else
        {
            // clang-format off
            if      (sf::Keyboard::Num1 == event.key.code) { m_editor.setFloor(context, Floor::Stone);}
            else if (sf::Keyboard::Num2 == event.key.code) { m_editor.setFloor(context, Floor::Wood); }
            else if (sf::Keyboard::Num3 == event.key.code) { m_editor.setFloor(context, Floor::Dirt); }
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

        if (sf::Keyboard::H == event.key.code)
        {
            // clang-format off
            std::cout << 
                "----------------------------------\n"
                "  Escape    - Quit the map editor.\n"
                "  h         - See this help text.\n"
                "  CNTRL-S   - Save the map.\n"
                "  Spacebar  - Bare Floor\n"
                "  Delete    - Clear Cell\n"
                "  Period    - (same as Delete)\n"
                "  l         - Lava\n"
                "  w         - Water\n"
                "  r         - Rock\n"
                "  d         - Door\n"
                "  D         - Locked Door\n"
                "  s         - Stairway Down\n"
                "  S         - Stairway Up\n"
                "  b         - Barrel\n"
                "  c         - Coffin\n"
                "  1,2,3     - Floor Type\n"
                "  CNTRL-R   - ERASE EVERYTHING!\n"
                "----------------------------------\n"
                << std::endl;
            // clang-format on
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
