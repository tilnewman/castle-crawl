// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// pieces.cpp
//
#include "pieces.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "keys.hpp"
#include "media.hpp"
#include "random.hpp"
#include "settings.hpp"
#include "sound-player.hpp"
#include "util.hpp"

#include <cassert>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace castlecrawl
{

    PieceBase::PieceBase()
        : m_mapChar{ '.' }
        , m_isObstacle{ true }
        , m_sprite{}
        , m_shaker()
        , m_shakeTimerSec(0.0f)
        , m_position()
    {}

    void PieceBase::reset(
        Context & context, const MapPos_t & pos, const char mapChar, const bool isObstacle)
    {
        m_mapChar = mapChar;
        m_isObstacle = isObstacle;
        m_sprite = context.media.sprite(mapCharToTileImage(mapChar));
        m_position = pos;
        m_sprite.setPosition(util::position(context.layout.cellBounds(pos)));
    }

    void PieceBase::move(Context & context, const sf::Keyboard::Key dir)
    {
        if (dir == sf::Keyboard::Up)
        {
            --m_position.y;
            m_sprite.move(0.0f, -context.layout.mapCellDimm());
        }
        else if (dir == sf::Keyboard::Down)
        {
            ++m_position.y;
            m_sprite.move(0.0f, context.layout.mapCellDimm());
        }
        else if (dir == sf::Keyboard::Left)
        {
            --m_position.x;
            m_sprite.move(-context.layout.mapCellDimm(), 0.0f);
        }
        else if (dir == sf::Keyboard::Right)
        {
            ++m_position.x;
            m_sprite.move(context.layout.mapCellDimm(), 0.0f);
        }
    }

    void PieceBase::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
    }

    void PieceBase::update(Context & context, const float frameTimeSec)
    {
        m_shakeTimerSec -= frameTimeSec;
        if (m_shakeTimerSec > 0.0f)
        {
            m_shaker.update(frameTimeSec);
            shake(context);
        }
    }

    void PieceBase::shake(Context & context)
    {
        sf::Vector2f pos{ util::position(context.layout.cellBounds(m_position)) };
        pos.x += m_shaker.adjustment();
        m_sprite.setPosition(pos);
    }

} // namespace castlecrawl
