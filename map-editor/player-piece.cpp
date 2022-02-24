// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// player-piece.cpp
//
#include "player-piece.hpp"

#include "../src/check-macros.hpp"
#include "board.hpp"
#include "door-piece.hpp"
#include "keys.hpp"
#include "settings.hpp"
#include "sound-player.hpp"

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

        if (keys::isArrow(key))
        {
            handleArrowKey(context, key);
        }
    }

    void PlayerPiece::handleArrowKey(Context & context, const sf::Keyboard::Key arrowKey)
    {
        move(context, arrowKey);
    }

} // namespace castlecrawl
