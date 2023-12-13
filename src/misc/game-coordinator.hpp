#ifndef CASTLECRAWL_GAMECOORDINATOR_HPP_INCLUDED
#define CASTLECRAWL_GAMECOORDINATOR_HPP_INCLUDED
//
// game-coordinator.hpp
//
#include "audio/music-player.hpp"
#include "audio/sound-player.hpp"
#include "display/animation-player.hpp"
#include "display/layout.hpp"
#include "display/media.hpp"
#include "display/popup-manager.hpp"
#include "display/tile-image.hpp"
#include "item/item-factory.hpp"
#include "map/board.hpp"
#include "map/maps.hpp"
#include "map/summoner.hpp"
#include "misc/config.hpp"
#include "misc/context.hpp"
#include "misc/game.hpp"
#include "misc/keys.hpp"
#include "misc/platform.hpp"
#include "misc/player.hpp"
#include "misc/random.hpp"
#include "misc/save-game.hpp"
#include "state/process.hpp"
#include "state/state-machine.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace castlecrawl
{
    class GameCoordinator
    {
      public:
        GameCoordinator();

        void run(const GameConfig & config);

      protected:
        void openWindow();
        void openWindowMacOS();
        void handleEvents();
        void update(const float elapsedTimeSec);
        void draw();

      protected:
        sf::RenderWindow m_window;

        Maps m_maps;
        Media m_media;
        Board m_board;
        Layout m_layout;
        Player m_player;
        Process m_process;
        GameInPlay m_game;
        GameConfig m_config;
        SaveGame m_saveGame;
        Summoners m_summoner;
        StateMachine m_states;
        PopupManager m_popups;
        item::ItemFactory m_items;
        util::Random m_random;
        util::SoundPlayer m_audio;
        util::MusicPlayer m_music;
        util::AnimationPlayer m_anim;
        util::Platform m_platform;

        Context m_context;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_GAMECOORDINATOR_HPP_INCLUDED
