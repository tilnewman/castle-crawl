// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-inventory.cpp
//
#include "state-inventory.hpp"

#include "board.hpp"
#include "context.hpp"
#include "keys.hpp"
#include "media.hpp"
#include "player-piece.hpp"
#include "popup-manager.hpp"
#include "process.hpp"
#include "settings.hpp"
#include "sound-player.hpp"
#include "state-machine.hpp"
#include "util.hpp"

namespace castlecrawl
{
    StateInventory::StateInventory(Context & context)
        : StatePlay(context)
        , m_statsRegion()
        , m_unItemsRegion()
        , m_eqItemsRegion()
        , m_bgFadeVerts()
        , m_bgBorderVerts()
    {}

    void StateInventory::onEnter(Context & context)
    {
        util::appendQuadVerts(
            context.layout.windowBounds(), m_bgFadeVerts, sf::Color(0, 0, 0, 150));

        const sf::Color backgroundColor(40, 40, 40, 230);
        const sf::Color borderColor(127, 127, 127);

        const sf::Vector2f windowSize{ context.layout.windowSize() };
        const float topPad{ std::floor(windowSize.y * 0.1f) };

        m_statsRegion.width = std::floor(windowSize.x * 0.5f);
        m_statsRegion.height = std::floor(windowSize.y * 0.225f);
        m_statsRegion.top = topPad;
        m_statsRegion.left = ((windowSize.x * 0.5f) - (m_statsRegion.width * 0.5f));

        const float betweenPad{ std::ceil(m_statsRegion.height * 0.02f) };

        m_unItemsRegion.width = std::floor(windowSize.x * 0.375f);
        m_unItemsRegion.height = (m_statsRegion.height * 2.0f);
        m_unItemsRegion.top = (util::bottom(m_statsRegion) + betweenPad);

        m_unItemsRegion.left =
            ((windowSize.x * 0.5f) - m_unItemsRegion.width) - (betweenPad * 0.5f);

        m_eqItemsRegion = m_unItemsRegion;
        m_eqItemsRegion.left = ((windowSize.x * 0.5f) + (betweenPad * 0.5f));

        util::appendQuadVerts(m_statsRegion, m_bgFadeVerts, backgroundColor);
        util::appendQuadVerts(m_unItemsRegion, m_bgFadeVerts, backgroundColor);
        util::appendQuadVerts(m_eqItemsRegion, m_bgFadeVerts, backgroundColor);

        util::appendLineVerts(m_statsRegion, m_bgBorderVerts, borderColor);
        util::appendLineVerts(m_unItemsRegion, m_bgBorderVerts, borderColor);
        util::appendLineVerts(m_eqItemsRegion, m_bgBorderVerts, borderColor);
    }

    void StateInventory::handleEvent(Context & context, const sf::Event & event)
    {
        if (sf::Event::KeyPressed != event.type)
        {
            return;
        }

        if (sf::Keyboard::Escape == event.key.code)
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
    }

} // namespace castlecrawl
