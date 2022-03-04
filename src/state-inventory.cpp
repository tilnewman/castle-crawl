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
    {}

    void StateInventory::onEnter(Context & context)
    {
        util::appendQuadVerts(
            context.layout.windowBounds(), m_bgFadeVerts, sf::Color(0, 0, 0, 150));
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
    }

} // namespace castlecrawl
