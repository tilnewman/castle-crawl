// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// pieces.cpp
//
#include "board.hpp"

#include "context.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace castlecrawl
{

    void Board::update(Context& context, const float frameTimeSec) 
    { 
        player.update(context, frameTimeSec);

        for (DoorPiece & door : doors)
        {
            door.update(context, frameTimeSec);
        }
    }

    void Board::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        // Don't draw doors (they are drawn by the character map)
        target.draw(player, states);
    }
} // namespace castlecrawl
