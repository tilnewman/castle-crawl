#ifndef CASTLECRAWL_STATEPLAY_HPP_INCLUDED
#define CASTLECRAWL_STATEPLAY_HPP_INCLUDED
//
// state-play.hpp
//
#include "frames-per-sec.hpp"
#include "states.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Window/Event.hpp>
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

        void update(Context &, const float frameTimeSec) override;
        void handleEvent(Context & context, const sf::Event & event) override;
        void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const override;

      private:
        FramesPerSecond m_fps;
        sf::RectangleShape m_windowOutline;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_STATEPLAY_HPP_INCLUDED
