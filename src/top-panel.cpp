// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// top-panel.cpp
//
#include "top-panel.hpp"

#include "context.hpp"
#include "layout.hpp"
#include "media.hpp"
#include "util.hpp"

namespace castlecrawl
{
    TopPanel::TopPanel()
        : m_titleSprite()
    {}

    void TopPanel::setup(Context & context)
    {
        // the top region reaches too far down into the map so make height adjustment here
        sf::FloatRect region{ context.layout.topRegion() };
        const float vertPad{ region.height * 0.1f };
        region.height -= vertPad;

        m_rectangle.setFillColor(context.config.background_color);
        m_rectangle.setOutlineColor(sf::Color(70, 70, 70));
        m_rectangle.setOutlineThickness(1.0f);
        m_rectangle.setSize(util::size(region));

        m_titleSprite.setTexture(context.media.titleTexture());

        const sf::FloatRect titleRect{
            0.0f, 0.0f, region.width, (region.height - (vertPad * 4.0f))
        };

        util::fit(m_titleSprite, titleRect);

        m_titleSprite.setPosition(
            ((region.width * 0.5f) - (m_titleSprite.getGlobalBounds().width * 0.5f)), vertPad);
    }

    void TopPanel::update() {}

    void TopPanel::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_rectangle, states);
        target.draw(m_titleSprite, states);
    }

} // namespace castlecrawl
