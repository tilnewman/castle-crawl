#ifndef CASTLECRAWL_PIECES_HPP_INCLUDED
#define CASTLECRAWL_PIECES_HPP_INCLUDED
//
// pieces.hpp
//
#include "display/shaker.hpp"
#include "display/tile-image.hpp"
#include "map/map-types.hpp"

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
        Player,
        DoorLocked,
        DoorUnlocked,
        Wall,
        Barrel,
        Coffin,
        Chest,
        Lava,
        Water,
        Slime,
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

    using PiecesOpt_t = std::optional<Pieces>;

    inline constexpr bool isPieceObstacle(const Pieces piece) noexcept
    {
        if ((piece == Pieces::Player) || (piece == Pieces::DoorUnlocked) ||
            (piece == Pieces::StairsDown) || (piece == Pieces::StairsUp))
        {
            return false;
        }
        else
        {
            return true;
        }
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
