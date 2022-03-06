// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// gui-listbox.cpp
//
#include "gui-listbox.hpp"

#include "context.hpp"
#include "util.hpp"

#include <SFML/Window/Event.hpp>

namespace castlecrawl
{
    Listbox::Listbox(item::ItemVec_t & items)
        : m_items(items)
        , m_hasFocus()
        , m_highlightColor(20, 20, 20, 20)
        , m_bgRectangle()
        , m_displayIndex(0)
        , m_selectIndex(0)
        , m_rowRects()
        , m_rowLineVerts()
        , m_rowTexts()
        , m_selectionRectangle()
    {}

    void Listbox::setupSize(
        const Context & context,
        const FontSize fontSize,
        const std::size_t widthCharsMax,
        const std::size_t heightRows)
    {
        const sf::Vector2f letterSize = context.media.fontExtent(fontSize).letter_size;

        m_bgRectangle.setSize({ (letterSize.x * static_cast<float>(widthCharsMax)),
                                (letterSize.y * static_cast<float>(heightRows)) });

        m_rowRects.clear();
        float posTop = m_bgRectangle.getGlobalBounds().top;
        for (std::size_t i = 0; i < heightRows; ++i)
        {
            sf::FloatRect rect{ m_bgRectangle.getGlobalBounds() };
            rect.height = (m_bgRectangle.getGlobalBounds().height / static_cast<float>(heightRows));
            rect.top = posTop;
            posTop += rect.height;
            m_rowRects.push_back(rect);
        }

        m_rowTexts.clear();
        for (std::size_t i = 0; i < heightRows; ++i)
        {
            std::string rowString;
            if (i < m_items.size())
            {
                rowString = m_items[i].name();
            }

            sf::Text & text = m_rowTexts.emplace_back(context.media.makeText(fontSize, rowString));
            text.setPosition(util::position(m_rowRects[i]));
        }

        m_selectionRectangle.setFillColor(sf::Color(255, 255, 255, 20));
        m_selectionRectangle.setOutlineThickness(0.0f);
        m_selectionRectangle.setSize(util::size(m_rowRects[0]));

        redraw();
    }

    void Listbox::setFocus(const bool hasFocus)
    {
        m_hasFocus = hasFocus;
        redraw();
    }

    void Listbox::setPosition(const sf::Vector2f & pos)
    {
        const sf::Vector2f move{ pos - util::position(m_bgRectangle) };
        m_bgRectangle.move(move);

        for (sf::FloatRect & rect : m_rowRects)
        {
            rect.left += move.x;
            rect.top += move.y;
        }

        for (sf::Text & text : m_rowTexts)
        {
            text.move(move);
        }

        redraw();
    }

    void Listbox::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(&m_rowLineVerts[0], m_rowLineVerts.size(), sf::PrimitiveType::Lines);
        target.draw(m_bgRectangle, states);

        for (const sf::Text & text : m_rowTexts)
        {
            target.draw(text, states);
        }

        if (m_hasFocus && !m_items.empty())
        {
            target.draw(m_selectionRectangle, states);
        }
    }

    void Listbox::handleEvent(const sf::Event &)
    {
        if (!m_hasFocus || m_items.empty())
        {
            return;
        }
    }

    bool Listbox::selectNext()
    {
        if ((m_selectIndex < (m_items.size() - 1_st)) && (m_selectIndex < (m_rowRects.size() - 1)))
        {
            ++m_selectIndex;
            redraw();
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Listbox::selectPrev()
    {
        if (m_selectIndex > 0)
        {
            --m_selectIndex;
            redraw();
            return true;
        }
        else
        {
            return false;
        }
    }

    void Listbox::redraw()
    {
        m_bgRectangle.setOutlineThickness(1.0f);

        m_bgRectangle.setFillColor(sf::Color(40, 40, 40, 127));
        m_bgRectangle.setOutlineColor(sf::Color(150, 150, 150, 127));

        if (m_hasFocus)
        {
            m_bgRectangle.setFillColor(m_bgRectangle.getFillColor() + m_highlightColor);
            m_bgRectangle.setOutlineColor(m_bgRectangle.getOutlineColor() + m_highlightColor);
        }

        m_rowLineVerts.clear();
        for (const sf::FloatRect & rect : m_rowRects)
        {
            util::appendLineVerts(rect, m_rowLineVerts, sf::Color(100, 100, 100, 127));
        }

        for (std::size_t i = 0; i < m_rowRects.size(); ++i)
        {
            std::string rowString;
            if (i < m_items.size())
            {
                rowString = m_items[i].name();
            }

            m_rowTexts[i].setString(rowString);
        }

        m_selectionRectangle.setPosition(util::position(m_rowRects[m_selectIndex]));
    }

} // namespace castlecrawl
