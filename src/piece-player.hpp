#ifndef CASTLECRAWL_PIECE_PLAYER_HPP_INCLUDED
#define CASTLECRAWL_PIECE_PLAYER_HPP_INCLUDED
//
// piece-player.hpp
//
#include "pieces.hpp"

namespace castlecrawl
{
    struct Context;

    class PlayerPiece : public PieceBase
    {
      public:
        PlayerPiece();
        PlayerPiece(Context & context, const MapPos_t pos);
        void handleEvent(Context &, const sf::Event &) override;
        void update(Context & context, const float frameTimeSec) override;
        void handleArrowKey(Context &, const sf::Keyboard::Key arrowKey);
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_PIECE_PLAYER_HPP_INCLUDED
