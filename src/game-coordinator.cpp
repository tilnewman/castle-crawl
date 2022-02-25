// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// game-coordinator.cpp
//
#include "game-coordinator.hpp"

#include "util.hpp"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <memory>
#include <sstream>

#include <SFML/Graphics.hpp>

namespace castlecrawl
{
    GameCoordinator::GameCoordinator()
        : m_window()
        , m_maps()
        , m_media()
        , m_board()
        , m_layout()
        , m_game()
        , m_config()
        , m_states()
        , m_popups()
        , m_random()
        , m_audio(m_random)
        , m_anim(m_random)
        , m_context(
              m_game,
              m_maps,
              m_board,
              m_config,
              m_layout,
              m_media,
              m_states,
              m_popups,
              m_random,
              m_audio,
              m_anim)
    {}

    void GameCoordinator::setup(const GameConfig & configOrig)
    {
        m_config = configOrig;

        M_CHECK(
            std::filesystem::exists(m_config.media_dir_path),
            "Error:  The media path does not exist:" << m_config.media_dir_path);

        M_CHECK(std::filesystem::is_directory(m_config.media_dir_path), m_config.media_dir_path);

        m_game.reset();

        m_window.create(m_config.video_mode, m_config.game_name, sf::Style::Fullscreen);

        M_CHECK(
            m_window.isOpen(),
            "Failed to make and open the graphics window.  (sf::RenderWindow::isOpen() == false)");

        m_window.setFramerateLimit(m_config.frame_rate_limit);
        m_window.setKeyRepeatEnabled(false);

        m_config.video_mode.width = m_window.getSize().x;
        m_config.video_mode.height = m_window.getSize().y;
        m_config.video_mode.bitsPerPixel = m_window.getSettings().depthBits;

        // sometimes SFML repoprts 32bpp as zero, don't know why, don't really care
        if (0 == m_config.video_mode.bitsPerPixel)
        {
            m_config.video_mode.bitsPerPixel = 32;
        }

        m_layout.setupWindow(m_config);

        std::cout << "Game Window Cells: width_ratio=" << m_config.map_cell_size_ratio
                  << ", pixels=" << m_layout.mapCellDimm()
                  << ", grid=" << (m_layout.windowSize() / m_layout.mapCellSize()) << std::endl;

        m_audio.setMediaPath((m_config.media_dir_path / "sfx").string());
        m_audio.volume(75.0f);

        m_anim.setMediaPath((m_config.media_dir_path / "anim").string());

        m_media.load(m_config, m_layout, m_audio);

        // depends only on m_random only so passing context here is safe
        m_maps.load(m_context);

        m_context.switchToMap({ { 0, 0 }, "level-1-first-room", { 5, 3 } });

        m_states.setChangePending(State::Splash);
    }

    void GameCoordinator::run(const GameConfig & config)
    {
        setup(config);

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
                return;
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
