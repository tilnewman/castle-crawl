#ifndef CASTLECRAWL_STATEPLAY_HPP_INCLUDED
#define CASTLECRAWL_STATEPLAY_HPP_INCLUDED
//
// state-edit.hpp
//
#include "frames-per-sec.hpp"
#include "states.hpp"

#include <string>

#include <SFML/Graphics/RectangleShape.hpp>

namespace castlecrawl
{
    struct Context;

    class StateEdit : public StateBase
    {
      public:
        StateEdit(Context & context);

        void update(Context &, const float frameTimeSec) override;
        void handleEvent(Context & context, const sf::Event & event) override;
        void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const override;

      private:
        FramesPerSecond m_fps;
        sf::RectangleShape m_windowOutline;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_STATEPLAY_HPP_INCLUDED
