#ifndef CASTLECRAWL_BOARD_HPP_INCLUDED
#define CASTLECRAWL_BOARD_HPP_INCLUDED
//
// board.hpp
//
#include "piece-player.hpp"
#include "pieces.hpp"

#include <optional>
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

        Pieces whichAt(const MapPos_t pos) const;
        std::optional<Piece> at(const MapPos_t pos);
        void add(Context & context, const Pieces which, const char mapChar, const MapPos_t pos);
        void update(Context & context, const float frameTimeSec);
        void draw(sf::RenderTarget &, sf::RenderStates) const override;

        Piece & player() { return m_player; }

      private:
        Piece m_player;
        std::vector<Piece> m_pieces;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_BOARD_HPP_INCLUDED
