#ifndef CASTLECRAWL_STATESPLASH_HPP_INCLUDED
#define CASTLECRAWL_STATESPLASH_HPP_INCLUDED
//
// state-splash.hpp
//
#include "state/states.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

namespace sf
{
    class RenderTarget;
    class Event;
} // namespace sf

namespace castlecrawl
{
    class StateSplash : public StateBase
    {
      public:
        StateSplash();

      protected:
        void update(Context &, const float) override;
        void handleEvent(Context &, const sf::Event &) override;
        void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const override;
        void onEnter(Context &) override;

      protected:
        enum class Timing
        {
            InitialWait = 0,
            FirstStrike,
            ShortWait,
            SecondStrike,
            LongWait
        };

        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::Clock m_clock;
        sf::Texture m_lightningTexture;
        sf::Sprite m_lightningSprite;
        Timing m_timing;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_STATESPLASH_HPP_INCLUDED
