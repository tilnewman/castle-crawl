// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// top-panel.cpp
//
#include "top-panel.hpp"

#include "context.hpp"
#include "layout.hpp"
#include "media.hpp"
#include "player.hpp"
#include "util.hpp"

namespace castlecrawl
{
    TopPanel::TopPanel()
        : m_titleSprite()
        , m_rectangle()
        , m_healthBar()
        , m_manaBar()
    {}

    void TopPanel::setup(Context & context)
    {
        // the map reaches up too far into the top panel so make height adjustment here
        sf::FloatRect region{ context.layout.topRegion() };
        const float vertPad{ region.height * 0.1f };
        region.height -= vertPad;

        // background color
        m_rectangle.setFillColor(context.config.background_color);
        m_rectangle.setOutlineColor(sf::Color(70, 70, 70));
        m_rectangle.setOutlineThickness(1.0f);
        m_rectangle.setSize(util::size(region));

        // title image
        m_titleSprite.setTexture(context.media.titleTexture());

        const sf::FloatRect titleRect{
            0.0f, 0.0f, region.width, (region.height - (vertPad * 4.0f))
        };

        util::fit(m_titleSprite, titleRect);

        m_titleSprite.setPosition(
            ((region.width * 0.5f) - (m_titleSprite.getGlobalBounds().width * 0.5f)), vertPad);

        // health bar
        const sf::FloatRect healthBarRect{
            1.0f, (region.height * 0.8f), (region.width * 0.3f), (region.height * 0.05f)
        };

        m_healthBar.setup(
            util::position(healthBarRect),
            util::size(healthBarRect),
            1.0f,
            sf::Color(255, 50, 50, 100));

        // mana bar
        const sf::FloatRect manaBarRect{ 1.0f,
                                         (util::bottom(healthBarRect) + healthBarRect.height),
                                         healthBarRect.width,
                                         healthBarRect.height };

        m_manaBar.setup(
            util::position(manaBarRect),
            util::size(manaBarRect),
            1.0f,
            sf::Color(50, 50, 255, 127));
    }

    void TopPanel::update(Context & context, const float)
    {
        m_healthBar.updateValue(context.player.health().ratio());
        m_manaBar.updateValue(context.player.mana().ratio());
    }

    void TopPanel::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_rectangle, states);
        target.draw(m_healthBar, states);
        target.draw(m_manaBar, states);
        target.draw(m_titleSprite, states);
    }

} // namespace castlecrawl
