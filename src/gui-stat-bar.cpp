// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// gui-stat-bar.cpp
//
#include "gui-stat-bar.hpp"

#include "util.hpp"

namespace castlecrawl
{
    StatBar::StatBar()
        : m_color()
        , m_width()
        , m_rect()
        , m_rectangle()
        , m_quadVerts()
    {}

    void StatBar::setup(
        const sf::Vector2f & pos,
        const sf::Vector2f & size,
        const float lineThickness,
        const sf::Color & color)
    {
        m_color = color;
        m_width = size.x;

        m_rectangle.setFillColor(sf::Color::Transparent);
        m_rectangle.setOutlineColor(color + sf::Color(100, 100, 100));
        m_rectangle.setOutlineThickness(lineThickness);
        m_rectangle.setPosition(pos);
        m_rectangle.setSize(size);

        m_rect.left = pos.x;
        m_rect.top = pos.y;
        m_rect.width = size.x;
        m_rect.height = size.y;

        util::appendQuadVerts(m_rect, m_quadVerts, m_color);
    }

    void StatBar::updateValue(const float valueRatio)
    {
        m_quadVerts.clear();

        m_rect.width = (m_width * valueRatio);

        util::appendQuadVerts(m_rect, m_quadVerts, m_color);
    }

    void StatBar::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(&m_quadVerts[0], m_quadVerts.size(), sf::PrimitiveType::Quads, states);
        target.draw(m_rectangle, states);
    }

} // namespace castlecrawl
