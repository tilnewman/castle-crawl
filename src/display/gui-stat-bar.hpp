#ifndef CASTLECRAWL_GUI_STAT_BAR_HPP_INCLUDED
#define CASTLECRAWL_GUI_STAT_BAR_HPP_INCLUDED
//
// gui-stat-bar.hpp
//
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Vertex.hpp>

namespace sf
{
    class RenderTarget;
} // namespace sf

namespace castlecrawl
{
    class StatBar : public sf::Drawable
    {
      public:
        StatBar();

        void setup(
            const sf::Vector2f & pos,
            const sf::Vector2f & size,
            const float lineThickness,
            const sf::Color & color);

        void updateValue(const float valueRatio);

        const sf::FloatRect getGlobalBounds() const { return m_rectangle.getGlobalBounds(); }

        void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

      private:
        sf::Color m_color;
        float m_width;
        sf::FloatRect m_rect;
        sf::RectangleShape m_rectangle;
        std::vector<sf::Vertex> m_quadVerts;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_GUI_STAT_BAR_HPP_INCLUDED
