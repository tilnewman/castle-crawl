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
#include "music-player.hpp"
#include "settings.hpp"
#include "sound-player.hpp"
#include "tile-image.hpp"

#include <SFML/Window/Event.hpp>

namespace castlecrawl
{
    void PlayerPiece::reset(Context & context, const MapPos_t & pos)
    {
        PieceBase::reset(context, pos, tileImageChar(TileImage::Player), false);
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

        // leave the map cases
        for (const MapLink & link : context.maps.get().links())
        {
            if (link.from_pos == newPos)
            {
                const char currentChar = context.maps.get().getChar(position());

                if ((currentChar == tileImageChar(TileImage::StairUp)) ||
                    (currentChar == tileImageChar(TileImage::StairDown)))
                {
                    context.audio.play("stairs.ogg");
                }

                context.maps.switchTo(context, link);
                return;
            }
        }

        const char newChar = context.maps.get().getChar(newPos);

        // wall bump cases
        if ((newChar != ' ') && (newChar != tileImageChar(TileImage::DoorLocked)) &&
            (newChar != tileImageChar(TileImage::Door)) &&
            (newChar != tileImageChar(TileImage::StairUp)) &&
            (newChar != tileImageChar(TileImage::StairDown)))
        {
            if (newChar == tileImageChar(TileImage::Lava))
            {
                context.audio.play("burn.ogg");
            }
            else if (newChar == tileImageChar(TileImage::Water))
            {
                context.audio.play("splash.ogg");
            }
            else
            {
                context.audio.play("tap-wood-low.ogg");
            }

            return;
        }

        // walk onto door cases
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

        const std::size_t lavaAroundCount = context.maps.get().countCharsAround(position(), 'l');
        if (lavaAroundCount == 0)
        {
            context.music.stop("lava.ogg");
        }
        else
        {
            context.music.start("lava.ogg");
        }

        const std::size_t waterAroundCount = context.maps.get().countCharsAround(position(), 'w');
        if (waterAroundCount == 0)
        {
            context.music.stop("water-bubbles.ogg");
        }
        else
        {
            context.music.start("water-bubbles.ogg");
        }
    }

} // namespace castlecrawl
