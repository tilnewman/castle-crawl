#ifndef CASTLECRAWL_BOARD_HPP_INCLUDED
#define CASTLECRAWL_BOARD_HPP_INCLUDED
//
// board.hpp
//
#include "map/pieces.hpp"

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

        Pieces whichAt(const MapPos_t & pos) const;
        PieceOpt_t at(const MapPos_t & pos);

        void add(const Piece & piece) { m_pieces.push_back(piece); }
        void remove(const MapPos_t & pos);
        void remove(const Pieces which);

        void update(Context & context, const float frameTimeSec);
        void draw(sf::RenderTarget &, sf::RenderStates) const override;

        Piece & player() { return m_player; }

      private:
        Piece m_player;
        std::vector<Piece> m_pieces;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_BOARD_HPP_INCLUDED
