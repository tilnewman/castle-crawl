#ifndef CASTLECRAWL_PIECE_DOOR_HPP_INCLUDED
#define CASTLECRAWL_PIECE_DOOR_HPP_INCLUDED
//
// piece-door.hpp
//
#include "pieces.hpp"

namespace castlecrawl
{
    struct Context;

    class DoorPiece : public PieceBase
    {
      public:
        DoorPiece(Context & context, const Piece piece, const char mapChar, const MapPos_t & pos)
            : PieceBase(context, piece, mapChar, pos)
        {}
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_DOOR_PIECE_HPP_INCLUDED
