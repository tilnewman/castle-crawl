#ifndef CASTLECRAWL_PIECES_HPP_INCLUDED
#define CASTLECRAWL_PIECES_HPP_INCLUDED
//
// pieces.hpp
//
#include "map-types.hpp"
#include "shaker.hpp"
#include "tile-image.hpp"

#include <SFML/Graphics/Drawable.hpp>
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

    enum class Pieces
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

    inline constexpr bool isPieceObstacle(const Pieces piece) noexcept
    {
        return !((Pieces::Player == piece) || (Pieces::DoorUnlocked == piece));
    }

    inline constexpr std::string_view toString(const Pieces piece) noexcept
    {
        // clang-format off
        switch (piece)
        {
            case Pieces::Player:        { return "Player"; }
            case Pieces::DoorLocked:    { return "DoorLocked"; }
            case Pieces::DoorUnlocked:  { return "DoorUnlocked"; }
            case Pieces::Wall:          { return "Wall"; }
            case Pieces::Barrel:        { return "Barrel"; }
            case Pieces::Coffin:        { return "Coffin"; }
            case Pieces::Chest:         { return "Chest"; }
            case Pieces::Lava:          { return "Lava"; }
            case Pieces::Water:         { return "Water"; }
            case Pieces::StairsUp:      { return "StairsUp"; }
            case Pieces::StairsDown:    { return "StairsDown"; }
            default:                    { return "Piece::Invalid"; }
        }
        // clang-format on
    }

    //

    class Piece : public sf::Drawable
    {
      public:
        Piece(const Pieces which);
        Piece(Context & context, const Pieces which, const char mapChar, const MapPos_t & pos);

        Pieces which() const { return m_which; }
        bool isObstacle() const { return isPieceObstacle(m_which); }

        MapPos_t position() const { return m_position; }
        void position(Context & context, const MapPos_t pos);

        void move(Context & context, const sf::Keyboard::Key dir);

        void update(Context & context, const float frameTimeSec);
        void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

        void shake() { m_shakeTimerSec = 1.0f; }

      private:
        void shake(Context & context);

      protected:
        Pieces m_which;
        sf::Sprite m_sprite;
        Shaker m_shaker;
        float m_shakeTimerSec;
        MapPos_t m_position;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_PIECES_HPP_INCLUDED
