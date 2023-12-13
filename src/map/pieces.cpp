// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// pieces.cpp
//
#include "map/pieces.hpp"

#include "misc/check-macros.hpp"
#include "misc/context.hpp"
#include "misc/keys.hpp"
#include "display/layout.hpp"
#include "display/media.hpp"
#include "misc/random.hpp"
#include "audio/sound-player.hpp"
#include "misc/sfml-util.hpp"

#include <cassert>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace castlecrawl
{

    Piece::Piece(const Pieces which)
        : m_which(which)
        , m_sprite()
        , m_shaker()
        , m_shakeTimerSec(0.0f)
        , m_position()
    {}

    Piece::Piece(Context & context, const Pieces which, const char mapChar, const MapPos_t & pos)
        : m_which(which)
        , m_sprite(context.media.tileSprite(tileImage(mapChar)))
        , m_shaker()
        , m_shakeTimerSec(0.0f)
        , m_position()
    {
        position(context, pos); // to set the sprite's position
    }

    void Piece::position(Context & context, const MapPos_t & pos)
    {
        m_position = pos;
        m_sprite.setPosition(util::position(context.layout.cellBounds(pos)));
    }

    void Piece::move(Context & context, const sf::Keyboard::Key key)
    {
        position(context, keys::moveIfDir(m_position, key));
    }

    void Piece::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
    }

    void Piece::update(Context & context, const float frameTimeSec)
    {
        m_shakeTimerSec -= frameTimeSec;
        if (m_shakeTimerSec > 0.0f)
        {
            m_shaker.update(frameTimeSec);
            shakeUpdate(context);
        }
    }

    void Piece::shakeUpdate(Context & context)
    {
        sf::Vector2f pos{ util::position(context.layout.cellBounds(m_position)) };
        pos.x += m_shaker.adjustment();
        m_sprite.setPosition(pos);
    }

} // namespace castlecrawl
