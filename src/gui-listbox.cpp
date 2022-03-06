// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// gui-listbox.cpp
//
#include "gui-listbox.hpp"

#include "context.hpp"
#include "util.hpp"

namespace castlecrawl
{
    Listbox::Listbox()
        : m_hasFocus()
        , m_highlightColor(20, 20, 20, 20)
        , m_bgRectangle()
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

        reset();
    }

    void Listbox::setFocus(const bool hasFocus)
    {
        m_hasFocus = hasFocus;
        reset();
    }

    void Listbox::setPosition(const sf::Vector2f & pos)
    {
        m_bgRectangle.setPosition(pos);
        reset();
    }

    void Listbox::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_bgRectangle, states);
    }

    void Listbox::handleEvent(const sf::Event &) {}

    void Listbox::reset()
    {
        m_bgRectangle.setOutlineThickness(1.0f);

        m_bgRectangle.setFillColor(sf::Color(40, 40, 40, 127));
        m_bgRectangle.setOutlineColor(sf::Color(100, 100, 100));

        if (m_hasFocus)
        {
            m_bgRectangle.setFillColor(m_bgRectangle.getFillColor() + m_highlightColor);
            m_bgRectangle.setOutlineColor(m_bgRectangle.getOutlineColor() + m_highlightColor);
        }
    }

    std::size_t Listbox::positionToIndex(const sf::Vector2f &)
    {
        // TODO
        return 0;
    }

} // namespace castlecrawl
