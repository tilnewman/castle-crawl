#ifndef CASTLECRAWL_STATEPLAY_HPP_INCLUDED
#define CASTLECRAWL_STATEPLAY_HPP_INCLUDED
//
// state-play.hpp
//
#include "display/top-panel.hpp"
#include "misc/frames-per-sec.hpp"
#include "state/states.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
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

    class StatePlay : public StateBase
    {
      public:
        StatePlay(Context & context);

        void onEnter(Context & context) override;
        void update(Context & context, const float frameTimeSec) override;
        void handleEvent(Context & context, const sf::Event & event) override;

        void draw(const Context & context, sf::RenderTarget & target, sf::RenderStates states)
            const override;

      private:
        void updateReplenish(Context & context, const float frameTimeSec);
        void updateSplat(const float frameTimeSec);

      private:
        static inline constexpr float m_replenishIntervalSec = 10.0f;
        static inline float m_replenishTimerSec = m_replenishIntervalSec;

        FramesPerSecond m_fps;
        sf::RectangleShape m_bgRectangle;
        TopPanel m_topPanel;

        float m_splatTimerSec;
        sf::Sprite m_splatSprite;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_STATEPLAY_HPP_INCLUDED
