#ifndef CASTLECRAWL_PIECES_HPP_INCLUDED
#define CASTLECRAWL_PIECES_HPP_INCLUDED
//
// pieces.hpp
//
#include "map-types.hpp"
#include "shaker.hpp"
#include "tile-image.hpp"

#include <functional>
#include <optional>

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
        None,
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
        StairsDown,
        Plant,
        Rock,
        //
        SnakeBag,
        SpiderWeb,
        GoblinPot,
        BirdMask,
        PixieGoblet,
        SkeletonGrave,
        DemonDoor,
        DragonBreath,
        WizardTomb,
        //
        Snake,
        Spider,
        Goblin,
        Bat,
        Pixie,
        Skeleton,
        Demon,
        Dragon,
        Wizard
    };

    inline constexpr bool isPieceObstacle(const Pieces piece) noexcept
    {
        // clang-format off
        switch (piece)
        {
            case Pieces::None:          { return false; }
            case Pieces::Player:        { return false; }
            case Pieces::DoorLocked:    { return true;  }
            case Pieces::DoorUnlocked:  { return false; }
            case Pieces::Wall:          { return true;  }
            case Pieces::Barrel:        { return true;  }
            case Pieces::Coffin:        { return true;  }
            case Pieces::Chest:         { return true;  }
            case Pieces::Lava:          { return true;  }
            case Pieces::Water:         { return true;  }
            case Pieces::StairsUp:      { return false; }
            case Pieces::StairsDown:    { return false; }
            case Pieces::Plant:         { return true;  }
            case Pieces::Rock:          { return true;  }
            //
            case Pieces::SnakeBag:      { return true;  }
            case Pieces::SpiderWeb:     { return true;  }
            case Pieces::GoblinPot:     { return true;  }
            case Pieces::BirdMask:      { return true;  }
            case Pieces::PixieGoblet:   { return true;  }
            case Pieces::SkeletonGrave: { return true;  }
            case Pieces::DemonDoor:     { return true;  }
            case Pieces::DragonBreath:  { return true;  }
            case Pieces::WizardTomb:    { return true;  }
            //
            case Pieces::Snake:         { return true;  }
            case Pieces::Spider:        { return true;  }
            case Pieces::Goblin:        { return true;  }
            case Pieces::Bat:           { return true;  }
            case Pieces::Pixie:         { return true;  }
            case Pieces::Skeleton:      { return true;  }
            case Pieces::Demon:         { return true;  }
            case Pieces::Dragon:        { return true;  }
            case Pieces::Wizard:        { return true;  }
            //
            default:                    { return false; }
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
        void position(Context & context, const MapPos_t & pos);

        void move(Context & context, const sf::Keyboard::Key dir);

        void update(Context & context, const float frameTimeSec);
        void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

        void shakeStart() { m_shakeTimerSec = 1.0f; }

      private:
        void shakeUpdate(Context & context);

      protected:
        Pieces m_which;
        sf::Sprite m_sprite;
        Shaker m_shaker;
        float m_shakeTimerSec;
        MapPos_t m_position;
    };

    using PieceOpt_t = std::optional<std::reference_wrapper<Piece>>;

} // namespace castlecrawl

#endif // CASTLECRAWL_PIECES_HPP_INCLUDED
