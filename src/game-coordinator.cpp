// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// game-coordinator.cpp
//
#include "game-coordinator.hpp"

#include <iostream>

namespace castlecrawl
{
    GameCoordinator::GameCoordinator()
        : m_window()
        , m_maps()
        , m_media()
        , m_board()
        , m_layout()
        , m_player()
        , m_process()
        , m_game()
        , m_config()
        , m_saveGame()
        , m_summoner()
        , m_states()
        , m_popups()
        , m_items()
        , m_random()
        , m_audio(m_random)
        , m_music()
        , m_anim(m_random)
        , m_context(
              m_game,
              m_player,
              m_maps,
              m_board,
              m_config,
              m_layout,
              m_process,
              m_media,
              m_summoner,
              m_states,
              m_popups,
              m_saveGame,
              m_items,
              m_random,
              m_audio,
              m_music,
              m_anim)
    {}

    void GameCoordinator::configureAndOpenWindow(const GameConfig & configOrig)
    {
        m_config = configOrig;

        m_window.create(m_config.video_mode, "Castle Crawl", sf::Style::Fullscreen);

        M_CHECK(
            m_window.isOpen(),
            "Error:  Failed to create() the fullscreen graphics window at "
                << m_config.video_mode.width << 'x' << m_config.video_mode.height);

        m_window.setFramerateLimit(m_config.frame_rate_limit);
        m_window.setKeyRepeatEnabled(false);

        m_config.setup(sf::VideoMode{
            m_window.getSize().x,
            m_window.getSize().y,
            m_window.getSettings().depthBits,
        });
    }

    void GameCoordinator::run(const GameConfig & configOrig)
    {
        configureAndOpenWindow(configOrig);

        m_context.state.setChangePending(State::Load);

        sf::Clock frameClock;
        while (m_window.isOpen() && !m_game.isGameOver())
        {
            handleEvents();
            update(frameClock.restart().asSeconds());
            draw();
            m_states.changeIfPending(m_context);
        }
    }

    void GameCoordinator::handleEvents()
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                std::cout << "Player closed the window.  Quitting." << std::endl;
                m_window.close();
                m_states.setChangePending(State::Quit);
                break;
            }

            m_states.state().handleEvent(m_context, event);
        }
    }

    void GameCoordinator::update(const float frameTimeSec)
    {
        m_states.state().update(m_context, frameTimeSec);
    }

    void GameCoordinator::draw()
    {
        m_window.clear();
        m_states.state().draw(m_context, m_window, sf::RenderStates());
        m_window.display();
    }

} // namespace castlecrawl
