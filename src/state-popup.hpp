#ifndef CASTLECRAWL_STATEPOPUP_HPP_INCLUDED
#define CASTLECRAWL_STATEPOPUP_HPP_INCLUDED
//
// state-popup.hpp
//
#include "state-play.hpp"

#include <SFML/Graphics/RenderStates.hpp>

namespace sf
{
    class RenderTarget;
    class Event;
} // namespace sf

namespace castlecrawl
{
    struct Context;

    //
    class StatePopup : public StatePlay
    {
      public:
        StatePopup(Context & context);

        void handleEvent(Context &, const sf::Event &) override;
        void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const override;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_STATEPOPUP_HPP_INCLUDED
