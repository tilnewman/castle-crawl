#ifndef CASTLECRAWL_STATEPAUSE_HPP_INCLUDED
#define CASTLECRAWL_STATEPAUSE_HPP_INCLUDED
//
// state-pause.hpp
//
#include "state-play.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Vertex.hpp>

namespace sf
{
    class RenderTarget;
    class Event;
} // namespace sf

namespace castlecrawl
{
    struct Context;

    //
    class StatePause : public StatePlay
    {
      public:
        StatePause(Context & context);

        void onEnter(Context & context) override;
        void handleEvent(Context &, const sf::Event &) override;
        void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const override;

        sf::Text m_text;
        std::vector<sf::Vertex> m_bgFadeVerts;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_STATEPAUSE_HPP_INCLUDED
