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
        void reset(Context & context, const MapPos_t & pos, const bool isLocked);

        bool isLocked() const { return isObstacle(); }
        void isLocked(const bool isLocked) { m_isObstacle = isLocked; }
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_DOOR_PIECE_HPP_INCLUDED
