#ifndef CASTLECRAWL_POPUPMANAGER_HPP_INCLUDED
#define CASTLECRAWL_POPUPMANAGER_HPP_INCLUDED
//
// popup-manager.hpp
//
#include <string>

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
        sf::Text text;
        sf::RectangleShape background_rectangle;
        sf::RectangleShape fade_rectangle;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_POPUPMANAGER_HPP_INCLUDED
