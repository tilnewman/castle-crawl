// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// pieces.cpp
//
#include "board.hpp"

#include "context.hpp"
#include "piece-door.hpp"
#include "util.hpp"

#include <sstream>

#include <SFML/Graphics/RenderTarget.hpp>

namespace castlecrawl
{
    Board::Board()
        : m_player()
        , m_pieces()
    {}

    void Board::update(Context & context, const float frameTimeSec)
    {
        m_player.update(context, frameTimeSec);

        for (IPieceUPtr_t & pieceUPtr : m_pieces)
        {
            pieceUPtr->update(context, frameTimeSec);
        }
    }

    void Board::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        for (const IPieceUPtr_t & pieceUPtr : m_pieces)
        {
            target.draw(*pieceUPtr, states);
        }

        target.draw(m_player, states);
    }

    void Board::add(Context & context, const Piece piece, const char mapChar, const MapPos_t pos)
    {
        // clang-format off
        switch (piece)
        {
            case Piece::DoorLocked:     { m_pieces.emplace_back(std::make_unique<DoorPiece>(context, piece, mapChar, pos)); break; }
            case Piece::DoorUnlocked:   { m_pieces.emplace_back(std::make_unique<DoorPiece>(context, piece, mapChar, pos)); break; }
            case Piece::Wall:           { m_pieces.emplace_back(std::make_unique<WallPiece>(context, piece, mapChar, pos)); break; }
            case Piece::Player:         
            case Piece::Barrel:
            case Piece::Coffin:
            case Piece::Chest:
            case Piece::Lava:
            case Piece::Water:
            case Piece::StairsUp:
            case Piece::StairsDown:
            default:
            {
                std::ostringstream ss;
                
                ss << "ERROR:  Board::add(" << toString(piece) << ", \'" << mapChar << ", " << pos
                          << "\") -That piece not handled in switch.  Nothing added!";

                throw std::runtime_error(ss.str());
            }
        }
        // clang-format on
    }

} // namespace castlecrawl
