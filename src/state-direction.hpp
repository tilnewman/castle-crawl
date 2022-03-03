#ifndef CASTLECRAWL_STATE_DIRECTION_HPP_INCLUDED
#define CASTLECRAWL_STATE_DIRECTION_HPP_INCLUDED
//
// state-direction.hpp
//
#include "state-play.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Window/Event.hpp>

namespace sf
{
    class RenderTarget;
} // namespace sf

namespace castlecrawl
{
    struct Context;

    class StateDirection : public StatePlay
    {
      public:
        StateDirection(Context & context);

        void onEnter(Context & context) override;
        void handleEvent(Context &, const sf::Event &) override;
        void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const override;

        static sf::Event m_closingEvent;
        static bool isClosingEventValid();

      private:
        sf::FloatRect m_up;
        sf::FloatRect m_down;
        sf::FloatRect m_left;
        sf::FloatRect m_right;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_STATE_DIRECTION_HPP_INCLUDED
