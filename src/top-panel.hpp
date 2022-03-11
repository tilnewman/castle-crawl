#ifndef CASTLECRAWL_TOP_PANEL_HPP_INCLUDED
#define CASTLECRAWL_TOP_PANEL_HPP_INCLUDED
//
// top-panel.hpp
//
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace castlecrawl
{
    struct Context;

    class TopPanel : public sf::Drawable
    {
      public:
        TopPanel();

        void setup(Context & context);
        void update();
        void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

      private:
        sf::Sprite m_titleSprite;
        sf::RectangleShape m_rectangle;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_TOP_PANEL_HPP_INCLUDED
