#ifndef CASTLECRAWL_STATE_TREASURE_HPP_INCLUDED
#define CASTLECRAWL_STATE_TREASURE_HPP_INCLUDED
//
// state-treasure.hpp
//
#include "item/item-factory.hpp"
#include "state/state-play.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Vertex.hpp>

namespace sf
{
    class RenderTarget;
    class Event;
} // namespace sf

namespace castlecrawl
{
    struct Context;

    class StateTreasure : public StatePlay
    {
      public:
        StateTreasure(Context & context);

        void onEnter(Context & context) override;
        void onExit(Context & context) override;
        void handleEvent(Context &, const sf::Event &) override;
        void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const override;
        void redraw(Context & context);

        static inline item::Treasure treasure = {};

      private:
        std::vector<sf::Vertex> m_bgFadeVerts;
        sf::Text m_titleText;
        sf::Text m_goldText;
        std::vector<sf::Text> m_itemTexts;
        sf::RectangleShape m_bgRectangle;
        sf::RectangleShape m_selectRectangle;
        std::size_t m_selectIndex;
        sf::Text m_doneText;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_STATE_TREASURE_HPP_INCLUDED
