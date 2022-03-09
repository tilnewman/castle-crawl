#ifndef CASTLECRAWL_GAMECOORDINATOR_HPP_INCLUDED
#define CASTLECRAWL_GAMECOORDINATOR_HPP_INCLUDED
//
// game-coordinator.hpp
//
#include "animation-player.hpp"
#include "board.hpp"
#include "context.hpp"
#include "item-factory.hpp"
#include "keys.hpp"
#include "maps.hpp"
#include "media.hpp"
#include "music-player.hpp"
#include "piece-player.hpp"
#include "player.hpp"
#include "popup-manager.hpp"
#include "process.hpp"
#include "random.hpp"
#include "settings.hpp"
#include "sound-player.hpp"
#include "state-machine.hpp"
#include "tile-image.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace castlecrawl
{
    class GameCoordinator
    {
      public:
        GameCoordinator();

        void run(const GameConfig & config);

      protected:
        void configureAndOpenWindow(const GameConfig & config);
        void handleEvents();
        void update(const float elapsedTimeSec);
        void draw();

      protected:
        sf::RenderWindow m_window;

        Maps m_maps;
        Media m_media;
        Board m_board;
        Layout m_layout;
        Process m_process;
        Player m_player;
        GameInPlay m_game;
        GameConfig m_config;
        StateMachine m_states;
        PopupManager m_popups;
        item::ItemFactory m_items;
        util::Random m_random;
        util::SoundPlayer m_audio;
        util::MusicPlayer m_music;
        util::AnimationPlayer m_anim;

        Context m_context;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_GAMECOORDINATOR_HPP_INCLUDED
