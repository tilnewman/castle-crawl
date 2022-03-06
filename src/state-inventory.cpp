// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-inventory.cpp
//
#include "state-inventory.hpp"

#include "board.hpp"
#include "context.hpp"
#include "item-factory.hpp"
#include "keys.hpp"
#include "media.hpp"
#include "player-piece.hpp"
#include "player.hpp"
#include "popup-manager.hpp"
#include "process.hpp"
#include "settings.hpp"
#include "sound-player.hpp"
#include "state-machine.hpp"
#include "util.hpp"

#include <string>

namespace castlecrawl
{
    StateInventory::StateInventory(Context & context)
        : StatePlay(context)
        , m_statsRegion()
        , m_unListbox(context.player.inventory().unItems())
        , m_eqListbox(context.player.inventory().eqItems())
        , m_bgFadeVerts()
        , m_bgBorderVerts()
        , m_healthBar()
        , m_manaBar()
        , m_statTextStr()
        , m_statTextAcc()
        , m_statTextDex()
        , m_statTextLck()
        , m_statTextArc()
    {}

    void StateInventory::update(Context & context, const float)
    {
        m_healthBar.updateValue(context.player.health().ratio());
        m_manaBar.updateValue(context.player.mana().ratio());

        m_statTextStr.setString(
            std::string("Strength:    ") + std::to_string(context.player.strength().current()) +
            "/" + std::to_string(context.player.strength().normal()));

        m_statTextAcc.setString(
            std::string("Accuracy:   ") + std::to_string(context.player.accuracy().current()) +
            "/" + std::to_string(context.player.accuracy().normal()));

        m_statTextDex.setString(
            std::string("Dexterity:  ") + std::to_string(context.player.dexterity().current()) +
            "/" + std::to_string(context.player.dexterity().normal()));

        m_statTextLck.setString(
            std::string("Luck:           ") + std::to_string(context.player.luck().current()) +
            "/" + std::to_string(context.player.luck().normal()));

        m_statTextArc.setString(
            std::string("Arcane:       ") + std::to_string(context.player.arcane().current()) +
            "/" + std::to_string(context.player.arcane().normal()));
    }

    void StateInventory::onEnter(Context & context)
    {
        util::appendQuadVerts(
            context.layout.windowBounds(), m_bgFadeVerts, sf::Color(0, 0, 0, 150));

        const sf::Color backgroundColor(40, 40, 40, 230);
        const sf::Color borderColor(127, 127, 127);

        const sf::Vector2f windowSize{ context.layout.windowSize() };
        const float topPad{ std::floor(windowSize.y * 0.1f) };

        // stats region
        const FontSize statFontSizeEnum{ FontSize::Medium };
        const sf::Vector2f statFontSize{ context.media.fontExtent(statFontSizeEnum).letter_size };
        const float totalTextHeight{ statFontSize.y * 5.0f };
        const float statsRegionPad{ std::floor(windowSize.x * 0.01f) };

        m_statsRegion.width = std::floor(windowSize.x * 0.5f);
        m_statsRegion.height = (totalTextHeight + (statsRegionPad * 3.0f));
        m_statsRegion.top = topPad;
        m_statsRegion.left = ((windowSize.x * 0.5f) - (m_statsRegion.width * 0.5f));

        const float betweenPad{ std::ceil(m_statsRegion.height * 0.02f) };

        // unequipped items region
        m_unListbox.setupSize(
            context, FontSize::Medium, context.items.textExtents().longest_name, 10_st);

        const float listboxTop = (util::bottom(m_statsRegion) + betweenPad);

        const float unEquippedPosLeft =
            ((windowSize.x * 0.5f) - m_unListbox.getGlobalBounds().width) - (betweenPad * 0.5f);

        m_unListbox.setPosition({ unEquippedPosLeft, listboxTop });

        // equipped items region
        m_eqListbox.setupSize(
            context, FontSize::Medium, context.items.textExtents().longest_name, 10_st);

        m_eqListbox.setPosition({ ((windowSize.x * 0.5f) + (betweenPad * 0.5f)), listboxTop });

        // region quads and lines
        util::appendQuadVerts(m_statsRegion, m_bgFadeVerts, backgroundColor);
        util::appendLineVerts(m_statsRegion, m_bgBorderVerts, borderColor);

        // stats text
        m_statTextStr = context.media.makeText(statFontSizeEnum, "");
        m_statTextAcc = context.media.makeText(statFontSizeEnum, "");
        m_statTextDex = context.media.makeText(statFontSizeEnum, "");
        m_statTextLck = context.media.makeText(statFontSizeEnum, "");
        m_statTextArc = context.media.makeText(statFontSizeEnum, "");

        m_statTextStr.setPosition(
            util::position(m_statsRegion) + sf::Vector2f(statsRegionPad, statsRegionPad));

        m_statTextAcc.setPosition(
            m_statTextStr.getPosition().x, util::bottom(m_statTextStr) + statFontSize.y);

        m_statTextDex.setPosition(
            m_statTextStr.getPosition().x, util::bottom(m_statTextAcc) + statFontSize.y);

        m_statTextLck.setPosition(
            m_statTextStr.getPosition().x, util::bottom(m_statTextDex) + statFontSize.y);

        m_statTextArc.setPosition(
            m_statTextStr.getPosition().x, util::bottom(m_statTextLck) + statFontSize.y);

        // health and mana bars
        const float statBarWidth{ std::floor(m_statsRegion.width * 0.6f) };
        const float statBarHeight{ std::ceil(m_statsRegion.height * 0.15f) };

        const sf::Vector2f barSize{ statBarWidth, statBarHeight };

        const float barLineThickness{ windowSize.x * 0.001f };

        const sf::Vector2f healthBarPos{ ((util::right(m_statsRegion) - statBarWidth) -
                                          (m_statsRegion.width * 0.1f)),
                                         (m_statsRegion.top + (m_statsRegion.height * 0.2f)) };

        m_healthBar.setup(healthBarPos, barSize, barLineThickness, sf::Color(235, 50, 50));

        const sf::Vector2f manaBarPos{
            healthBarPos.x, (util::bottom(m_healthBar) + (m_statsRegion.height * 0.2f))
        };

        m_manaBar.setup(manaBarPos, barSize, barLineThickness, sf::Color(60, 145, 240));
    }

    void StateInventory::handleEvent(Context & context, const sf::Event & event)
    {
        if (sf::Event::MouseButtonPressed == event.type)
        {
            const sf::Vector2f mousePos{ sf::Mouse::getPosition() };
            if (m_unListbox.getGlobalBounds().contains(mousePos))
            {
                m_unListbox.setFocus(true);
                m_eqListbox.setFocus(false);
            }
            else if (m_eqListbox.getGlobalBounds().contains(mousePos))
            {
                m_unListbox.setFocus(false);
                m_eqListbox.setFocus(true);
            }
        }

        m_unListbox.handleEvent(event);
        m_eqListbox.handleEvent(event);

        if (sf::Event::KeyPressed != event.type)
        {
            return;
        }

        if ((sf::Keyboard::Escape == event.key.code) || (sf::Keyboard::I == event.key.code))
        {
            context.state.setChangePending(State::Play);
        }
    }

    void StateInventory::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        StatePlay::draw(context, target, states);

        target.draw(&m_bgFadeVerts[0], m_bgFadeVerts.size(), sf::PrimitiveType::Quads);
        target.draw(&m_bgBorderVerts[0], m_bgBorderVerts.size(), sf::PrimitiveType::Lines);

        target.draw(m_healthBar, states);
        target.draw(m_manaBar, states);

        target.draw(m_statTextStr, states);
        target.draw(m_statTextAcc, states);
        target.draw(m_statTextDex, states);
        target.draw(m_statTextLck, states);
        target.draw(m_statTextArc, states);

        target.draw(m_unListbox);
        target.draw(m_eqListbox);
    }

} // namespace castlecrawl
