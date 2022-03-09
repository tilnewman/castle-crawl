#ifndef CASTLECRAWL_BOARD_HPP_INCLUDED
#define CASTLECRAWL_BOARD_HPP_INCLUDED
//
// board.hpp
//
#include "piece-player.hpp"
#include "pieces.hpp"

#include <vector>

#include <SFML/Graphics/RenderStates.hpp>

namespace sf
{
    class RenderTarget;
}

namespace castlecrawl
{
    struct Context;

    class Board : public sf::Drawable
    {
      public:
        Board();

        void clear() { m_pieces.clear(); }

        void add(Context & context, const Piece piece, const char mapChar, const MapPos_t pos);
        void update(Context & context, const float frameTimeSec);
        void draw(sf::RenderTarget &, sf::RenderStates) const override;

        PlayerPiece & player() { return m_player; }

      private:
        PlayerPiece m_player;

        // only ONE piece may be in each map position, which is why m_player is not in this vector
        std::vector<IPieceUPtr_t> m_pieces;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_BOARD_HPP_INCLUDED
