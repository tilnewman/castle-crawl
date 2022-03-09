#ifndef CASTLECRAWL_PIECES_HPP_INCLUDED
#define CASTLECRAWL_PIECES_HPP_INCLUDED
//
// pieces.hpp
//
#include "map-types.hpp"
#include "shaker.hpp"
#include "tile-image.hpp"

#include <memory>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace sf
{
    class RenderTarget;
    class Event;
} // namespace sf

namespace castlecrawl
{
    struct Context;

    enum class Piece
    {
        Player,
        DoorLocked,
        DoorUnlocked,
        Wall,
        Barrel,
        Coffin,
        Chest,
        Lava,
        Water,
        StairsUp,
        StairsDown
    };

    inline constexpr bool isPieceObstacle(const Piece piece) noexcept
    {
        return !((Piece::Player == piece) || (Piece::DoorUnlocked == piece));
    }

    inline constexpr std::string_view toString(const Piece piece) noexcept
    {
        // clang-format off
        switch (piece)
        {
            case Piece::Player:         { return "Player"; }
            case Piece::DoorLocked:     { return "DoorLocked"; }
            case Piece::DoorUnlocked:   { return "DoorUnlocked"; }
            case Piece::Wall:           { return "Wall"; }
            case Piece::Barrel:         { return "Barrel"; }
            case Piece::Coffin:         { return "Coffin"; }
            case Piece::Chest:          { return "Chest"; }
            case Piece::Lava:           { return "Lava"; }
            case Piece::Water:          { return "Water"; }
            case Piece::StairsUp:       { return "StairsUp"; }
            case Piece::StairsDown:     { return "StairsDown"; }
            default:                    { return "Piece::Invalid"; }
        }
        // clang-format on
    }

    struct IPiece : public sf::Drawable
    {
        virtual ~IPiece() override = default;

        virtual Piece which() const = 0;
        virtual bool isObstacle() const = 0;

        virtual MapPos_t position() const = 0;
        virtual void position(Context & context, const MapPos_t pos) = 0;

        virtual void move(Context & context, const sf::Keyboard::Key dir) = 0;

        virtual void handleEvent(Context &, const sf::Event &) = 0;
        void draw(sf::RenderTarget &, sf::RenderStates) const override = 0;

        virtual void update(Context & context, const float frameTimeSec) = 0;

        virtual void shake() = 0;
    };

    using IPieceUPtr_t = std::unique_ptr<IPiece>;

    //

    class PieceBase : public IPiece
    {
      public:
        PieceBase(const Piece which);
        PieceBase(Context & context, const Piece which, const char mapChar, const MapPos_t & pos);

        virtual ~PieceBase() override = default;

        Piece which() const final { return m_which; }
        bool isObstacle() const final { return isPieceObstacle(m_which); }

        MapPos_t position() const final { return m_position; }
        void position(Context & context, const MapPos_t pos) final;

        void move(Context & context, const sf::Keyboard::Key dir) override final;

        void handleEvent(Context &, const sf::Event &) override {}
        void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
        void update(Context & context, const float frameTimeSec) override;

        void shake() override { m_shakeTimerSec = 1.0f; }

      private:
        void shake(Context & context);

      protected:
        Piece m_which;
        sf::Sprite m_sprite;
        Shaker m_shaker;
        float m_shakeTimerSec;
        MapPos_t m_position;
    };

    //

    class WallPiece : public PieceBase
    {
      public:
        WallPiece(Context & context, const Piece piece, const char mapChar, const MapPos_t & pos)
            : PieceBase(context, piece, mapChar, pos)
        {}
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_PIECES_HPP_INCLUDED
