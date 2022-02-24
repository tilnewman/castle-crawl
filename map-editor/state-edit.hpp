#ifndef CASTLECRAWLMAPPER_STATEPLAY_HPP_INCLUDED
#define CASTLECRAWLMAPPER_STATEPLAY_HPP_INCLUDED
//
// state-edit.hpp
//
#include "frames-per-sec.hpp"
#include "states.hpp"

#include <string>

#include <SFML/Graphics/RectangleShape.hpp>

namespace mapper
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

} // namespace mapper

#endif // CASTLECRAWLMAPPER_STATEPLAY_HPP_INCLUDED
