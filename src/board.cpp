// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// pieces.cpp
//
#include "board.hpp"

#include "context.hpp"
#include "util.hpp"

#include <sstream>

#include <SFML/Graphics/RenderTarget.hpp>

namespace castlecrawl
{
    Board::Board()
        : m_player(Pieces::Player)
        , m_pieces()
    {}

    Pieces Board::whichAt(const MapPos_t & pos) const
    {
        for (const Piece & piece : m_pieces)
        {
            if (piece.position() == pos)
            {
                return piece.which();
            }
        }

        return Pieces::None;
    }

    PieceOpt_t Board::at(const MapPos_t & pos)
    {
        for (Piece & piece : m_pieces)
        {
            if (piece.position() == pos)
            {
                return piece;
            }
        }

        return std::nullopt;
    }

    void Board::update(Context & context, const float frameTimeSec)
    {
        m_player.update(context, frameTimeSec);

        for (Piece & piece : m_pieces)
        {
            piece.update(context, frameTimeSec);
        }
    }

    void Board::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        for (const Piece & piece : m_pieces)
        {
            target.draw(piece, states);
        }

        target.draw(m_player, states);
    }

    void Board::remove(const MapPos_t & pos)
    {
        m_pieces.erase(
            std::remove_if(
                std::begin(m_pieces),
                std::end(m_pieces),
                [&](const Piece & piece) { return (piece.position() == pos); }),
            std::end(m_pieces));
    }

    void Board::remove(const Pieces which)
    {
        m_pieces.erase(
            std::remove_if(
                std::begin(m_pieces),
                std::end(m_pieces),
                [&](const Piece & piece) { return (piece.which() == which); }),
            std::end(m_pieces));
    }

} // namespace castlecrawl
