// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// player-piece.cpp
//
#include "player-piece.hpp"

#include "animation-player.hpp"
#include "board.hpp"
#include "check-macros.hpp"
#include "context.hpp"
#include "door-piece.hpp"
#include "keys.hpp"
#include "maps.hpp"
#include "settings.hpp"
#include "sound-player.hpp"

#include <SFML/Window/Event.hpp>

namespace castlecrawl
{
    void PlayerPiece::reset(Context & context, const MapPos_t & pos)
    {
        PieceBase::reset(context, pos, 'p', false);
    }

    void PlayerPiece::handleEvent(Context & context, const sf::Event & event)
    {
        if (sf::Event::KeyPressed != event.type)
        {
            return;
        }

        const sf::Keyboard::Key key{ event.key.code };

        handleArrowKey(context, key);
    }

    void PlayerPiece::update(Context & context, const float frameTimeSec)
    {
        PieceBase::update(context, frameTimeSec);
    }

    void PlayerPiece::handleArrowKey(Context & context, const sf::Keyboard::Key arrowKey)
    {
        if (!keys::isArrow(arrowKey))
        {
            return;
        }

        const MapPos_t newPos = keys::moveIfDir(position(), arrowKey);

        for (const MapLink & link : context.maps.get().links())
        {
            if (link.from_pos == newPos)
            {
                const char currentChar = context.maps.get().getChar(position());

                if ((currentChar == 'S') || (currentChar == 's'))
                {
                    context.audio.play("stairs.ogg");
                }

                context.maps.switchTo(context, link);
                return;
            }
        }

        const char newChar = context.maps.get().getChar(newPos);

        if ((newChar != ' ') && (newChar != 'D') && (newChar != 'd') && (newChar != 'S') &&
            (newChar != 's'))
        {
            if (newChar == 'l')
            {
                context.audio.play("burn.ogg");
            }
            else if (newChar == 'w')
            {
                context.audio.play("splash.ogg");
            }
            else
            {
                context.audio.play("tap-wood-low.ogg");
            }

            return;
        }

        for (const DoorPiece & door : context.board.doors)
        {
            if (door.position() != newPos)
            {
                continue;
            }

            if (door.isLocked())
            {
                context.audio.play("locked.ogg");
                return;
            }
            else
            {
                move(context, arrowKey);
                context.audio.play("door-open.ogg");
                return;
            }
        }

        move(context, arrowKey);
        context.audio.play("tick-on-2.ogg");
    }

} // namespace castlecrawl
