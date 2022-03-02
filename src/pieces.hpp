#ifndef CASTLECRAWL_PIECES_HPP_INCLUDED
#define CASTLECRAWL_PIECES_HPP_INCLUDED
//
// pieces.hpp
//
#include "map-types.hpp"
#include "tile-image.hpp"
#include "shaker.hpp"

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

    struct IPiece : public sf::Drawable
    {
        virtual ~IPiece() override = default;

        virtual char mapChar() const = 0;
        virtual bool isObstacle() const = 0;

        virtual MapPos_t position() const = 0;

        // does NOT change the map!
        virtual void move(Context & context, const sf::Keyboard::Key dir) = 0;

        virtual void handleEvent(Context &, const sf::Event &) = 0;
        void draw(sf::RenderTarget &, sf::RenderStates) const override = 0;

        virtual void update(Context & context, const float frameTimeSec) = 0;
    };

    //

    class PieceBase : public IPiece
    {
      public:
        PieceBase();

        virtual ~PieceBase() override = default;

        char mapChar() const override final { return m_mapChar; }
        bool isObstacle() const override final { return m_isObstacle; }
        MapPos_t position() const override final { return m_position; }

        // keep this this ONLY way to move pieces, intentionally NOT changing the map!
        void move(Context & context, const sf::Keyboard::Key dir) override final;

        // does nothing by default
        void handleEvent(Context &, const sf::Event &) override {}

        void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

        void update(Context & context, const float frameTimeSec) override;

        void willShake(const bool enable) { m_willShake = enable; }

      protected:
        void reset(
            Context & context, const MapPos_t & pos, const char mapChar, const bool isObstacle);

      private:
        void shake(Context & context);

      protected:
        char m_mapChar;
        bool m_isObstacle;
        sf::Sprite m_sprite;
        
      private:
        Shaker m_shaker;
        bool m_willShake;
        MapPos_t m_position;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_PIECES_HPP_INCLUDED
