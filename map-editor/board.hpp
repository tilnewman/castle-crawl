#ifndef CASTLECRAWLMAPPER_BOARD_HPP_INCLUDED
#define CASTLECRAWLMAPPER_BOARD_HPP_INCLUDED
//
// board.hpp
//
#include "door-piece.hpp"
#include "player-piece.hpp"

#include <vector>

#include <SFML/Graphics/RenderTarget.hpp>

namespace mapper
{
    struct Board : public sf::Drawable
    {
        PlayerPiece player;
        std::vector<DoorPiece> doors;

        void draw(sf::RenderTarget &, sf::RenderStates) const override;
    };

} // namespace mapper

#endif // CASTLECRAWLMAPPER_PLAYER_HPP_INCLUDED
