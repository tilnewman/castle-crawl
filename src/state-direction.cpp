// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-direction.cpp
//
#include "state-direction.hpp"

#include "context.hpp"
#include "resources.hpp"
#include "settings.hpp"
#include "sound-player.hpp"
#include "state-machine.hpp"
#include "util.hpp"
#include "board.hpp"
#include "player-piece.hpp"
#include "keys.hpp"

namespace castlecrawl
{
    StateDirection::StateDirection(Context & context)
        : StatePlay(context)
        , m_up()
        , m_down()
        , m_left()
        , m_right()
    {}

    sf::Event StateDirection::m_closingEvent{};

    void StateDirection::onEnter(Context & context)
    {
        m_closingEvent = {};

        //TODO which sfx to play?
        //context.audio.play("pause");

        const MapPos_t upPos{ context.board.player.position() + MapPos_t{ 0, -1 } };
        const MapPos_t downPos{ context.board.player.position() + MapPos_t{ 0, 1 } };
        const MapPos_t leftPos{ context.board.player.position() + MapPos_t{ -1, 0 } };
        const MapPos_t rightPos{ context.board.player.position() + MapPos_t{ 1, 0 } };

        if (context.layout.isPositionValid(upPos))
        {
            m_up = context.layout.cellBounds(upPos);
        }
        else
        {
            m_up = {-1.0f, -1.0f, -1.0f, -1.0f};
        }

        if (context.layout.isPositionValid(downPos))
        {
            m_down = context.layout.cellBounds(downPos);
        }
        else
        {
            m_down = { -1.0f, -1.0f, -1.0f, -1.0f };
        }
        
        if (context.layout.isPositionValid(leftPos))
        {
            m_left = context.layout.cellBounds(leftPos);
        }
        else
        {
            m_left = { -1.0f, -1.0f, -1.0f, -1.0f };
        }

        if (context.layout.isPositionValid(rightPos))
        {
            m_right = context.layout.cellBounds(rightPos);
        }
        else
        {
            m_right = { -1.0f, -1.0f, -1.0f, -1.0f };
        }
    }

    void StateDirection::handleEvent(Context & context, const sf::Event & event)
    {
        if (sf::Event::KeyPressed != event.type)
        {
            return;
        }

        if ((sf::Keyboard::Escape == event.key.code) ||
            keys::isArrow(event.key.code))
        {
            m_closingEvent = event;
            context.state.setChangePending(State::Play);
        }
    }

    void StateDirection::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        StatePlay::draw(context, target, states);
        
        const sf::Color color(0,255,255,127);

        if (m_up.left > 0.0f)
        {
            util::drawRectangleShape(target, m_up, true, color);
        }

        if (m_down.left > 0.0f)
        {
            util::drawRectangleShape(target, m_down, true, color);
        }

        if (m_left.left > 0.0f)
        {
            util::drawRectangleShape(target, m_left, true, color);
        }

        if (m_right.left > 0.0f)
        {
            util::drawRectangleShape(target, m_right, true, color);
        }

    }

} // namespace castlecrawl
