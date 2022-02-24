#ifndef CASTLECRAWLMAPPER_GAMECOORDINATOR_HPP_INCLUDED
#define CASTLECRAWLMAPPER_GAMECOORDINATOR_HPP_INCLUDED
//
// game-coordinator.hpp
//
#include "board.hpp"
#include "context.hpp"
#include "keys.hpp"
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

      protected:
        void initializeSubsystems(const GameConfig & config);
        void openWindow();
        void handleEvents();
        void update(const float elapsedTimeSec);
        void draw();

      protected:
        sf::RenderWindow m_window;

        Media m_media;
        Board m_board;
        Layout m_layout;
        GameInPlay m_game;
        GameConfig m_config;
        StateMachine m_stateMachine;
        PopupManager m_popupManager;
        util::Random m_random;

        Context m_context;
    };

} // namespace mapper

#endif // CASTLECRAWLMAPPER_GAMECOORDINATOR_HPP_INCLUDED
