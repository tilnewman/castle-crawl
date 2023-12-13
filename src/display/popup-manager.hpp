#ifndef CASTLECRAWL_POPUPMANAGER_HPP_INCLUDED
#define CASTLECRAWL_POPUPMANAGER_HPP_INCLUDED
//
// popup-manager.hpp
//
#include "display/media.hpp"

#include <string>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

namespace castlecrawl
{
    struct Context;

    enum class PopupBackground
    {
        Banner,
        Paper1,
        Paper2
    };

    //

    class PopupManager : public sf::Drawable
    {
      public:
        PopupManager() = default;

        void setupBanner(Context & context, const std::string & message);

        void setupPaper(
            Context & context,
            const PopupBackground background,
            const FontSize fontSize,
            const sf::Color & color,
            const std::string & text);

        void draw(sf::RenderTarget &, sf::RenderStates) const override;

      private:
        std::vector<sf::Text> m_texts;
        sf::RectangleShape m_bgRectangle;
        sf::Sprite m_paperSprite;
        sf::RectangleShape m_fadeRectangle;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_POPUPMANAGER_HPP_INCLUDED
