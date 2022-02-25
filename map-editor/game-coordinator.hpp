#ifndef CASTLECRAWLMAPPER_GAMECOORDINATOR_HPP_INCLUDED
#define CASTLECRAWLMAPPER_GAMECOORDINATOR_HPP_INCLUDED
//
// game-coordinator.hpp
//
#include "board.hpp"
#include "context.hpp"
#include "editor.hpp"
#include "keys.hpp"
#include "map-tracker.hpp"
#include "player-piece.hpp"
#include "popup-manager.hpp"
#include "random.hpp"
#include "resources.hpp"
#include "settings.hpp"
#include "state-machine.hpp"
#include "tile-image.hpp"

#include <memory>
#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

namespace mapper
{
    class GameCoordinator
    {
      public:
        GameCoordinator();

        void run(const GameConfig & config);

      private:
        bool setup(const GameConfig & config);
        void openWindow();
        void handleEvents();
        void update(const float elapsedTimeSec);
        void draw();
        const std::filesystem::path findWhichFileToEdit();

      private:
        sf::RenderWindow m_window;
        sf::RenderStates m_renderStates;

        Media m_media;
        Board m_board;
        Layout m_layout;
        Editor m_editor;
        MapTracker m_map;
        GameConfig m_config;
        StateMachine m_state;
        PopupManager m_popup;
        util::Random m_random;

        Context m_context;
    };

} // namespace mapper

#endif // CASTLECRAWLMAPPER_GAMECOORDINATOR_HPP_INCLUDED
