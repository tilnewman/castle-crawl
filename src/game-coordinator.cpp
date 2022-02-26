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
        , m_game()
        , m_config()
        , m_states()
        , m_popups()
        , m_items()
        , m_random()
        , m_audio(m_random)
        , m_anim(m_random)
        , m_context(
              m_game,
              m_player,
              m_maps,
              m_board,
              m_config,
              m_layout,
              m_media,
              m_states,
              m_popups,
              m_items,
              m_random,
              m_audio,
              m_anim)
    {}

    void GameCoordinator::setup(const GameConfig & configOrig)
    {
        // Note that m_context is not safe to use until this function completes

        m_config = configOrig;

        m_game.reset();

        m_window.create(m_config.video_mode, "Castle Crawl", sf::Style::Fullscreen);

        M_CHECK(
            m_window.isOpen(),
            "Error:  Failed to create() the fullscreen graphics window at "
                << m_config.video_mode.width << 'x' << m_config.video_mode.height);

        m_config.setup(sf::VideoMode{
            m_window.getSize().x,
            m_window.getSize().y,
            m_window.getSettings().depthBits,
        });

        m_window.setFramerateLimit(m_config.frame_rate_limit);
        m_window.setKeyRepeatEnabled(false);

        m_layout.calcWindowValues(m_config);

        m_audio.setMediaPath((m_config.media_dir_path / "sfx").string());
        m_audio.volume(75.0f);

        m_anim.setMediaPath((m_config.media_dir_path / "anim").string());

        m_media.load(m_config, m_layout, m_audio);

        m_maps.loadAll(m_random);

        m_states.setChangePending(State::Splash);

        m_maps.switchTo(m_context, { { 0, 0 }, "level-1-first-room", { 5, 3 } });
    }

    void GameCoordinator::run(const GameConfig & configOrig)
    {
        setup(configOrig);

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
