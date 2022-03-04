#ifndef CASTLECRAWL_POPUPMANAGER_HPP_INCLUDED
#define CASTLECRAWL_POPUPMANAGER_HPP_INCLUDED
//
// popup-manager.hpp
//
#include <string>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

namespace castlecrawl
{
    struct Context;

    //
    class PopupManager : public sf::Drawable
    {
      public:
        PopupManager() = default;

        // prevent all copy and assignment
        PopupManager(const PopupManager &) = delete;
        PopupManager(PopupManager &&) = delete;
        //
        PopupManager & operator=(const PopupManager &) = delete;
        PopupManager & operator=(PopupManager &&) = delete;

        void setup(Context & context, const std::string & message);
        void draw(sf::RenderTarget &, sf::RenderStates) const override;

      private:
        std::vector<sf::Text> m_texts;
        sf::RectangleShape m_bgRectangle;
        sf::RectangleShape m_fadeRectangle;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_POPUPMANAGER_HPP_INCLUDED
