#ifndef CASTLECRAWL_STATE_INVENTORY_HPP_INCLUDED
#define CASTLECRAWL_STATE_INVENTORY_HPP_INCLUDED
//
// state-inventory.hpp
//
#include "state-play.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Window/Event.hpp>

namespace sf
{
    class RenderTarget;
} // namespace sf

namespace castlecrawl
{
    struct Context;

    class StateInventory : public StatePlay
    {
      public:
        StateInventory(Context & context);

        void onEnter(Context & context) override;
        void handleEvent(Context &, const sf::Event &) override;
        void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const override;

      private:
        sf::FloatRect m_statsRegion;
        sf::FloatRect m_unItemsRegion;
        sf::FloatRect m_eqItemsRegion;
        std::vector<sf::Vertex> m_bgFadeVerts;
        std::vector<sf::Vertex> m_bgBorderVerts;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_STATE_INVENTORY_HPP_INCLUDED