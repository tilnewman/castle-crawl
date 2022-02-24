#ifndef CASTLECRAWLMAPPER_PLAYER_HPP_INCLUDED
#define CASTLECRAWLMAPPER_PLAYER_HPP_INCLUDED
//
// player-piece.hpp
//
#include "pieces.hpp"

namespace mapper
{

    class PlayerPiece : public PieceBase
    {
      public:
        void reset(Context & context, const MapPos_t & pos);
        void handleEvent(Context &, const sf::Event &) override;
        void handleArrowKey(Context &, const sf::Keyboard::Key arrowKey);
    };

} // namespace mapper

#endif // CASTLECRAWLMAPPER_PLAYER_HPP_INCLUDED
