// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// game-coordinator.cpp
//
#include "game-coordinator.hpp"

#include "../src/check-macros.hpp"
#include "../src/util.hpp"

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
        , m_media()
        , m_board()
        , m_layout()
        , m_game()
        , m_config()
        , m_stateMachine()
        , m_popupManager()
        , m_random()
        , m_context(
              m_game,
              m_board,
              m_config,
              m_layout,
              m_media,
              m_stateMachine,
              m_popupManager,
              m_random)
    {}

    void GameCoordinator::initializeSubsystems(const GameConfig & config)
    {
        m_game.reset();

        m_config = config;
        M_CHECK(std::filesystem::exists(m_config.media_dir_path), m_config.media_dir_path);
        M_CHECK(std::filesystem::is_directory(m_config.media_dir_path), m_config.media_dir_path);

        // this can change m_config and m_layout so call this right after m_config is set
        openWindow();

        m_media.load(m_config, m_layout);

        m_stateMachine.setChangePending(State::Edit);
    }

    void GameCoordinator::openWindow()
    {
        m_window.close();

        const auto style{ (m_config.is_fullscreen) ? sf::Style::Fullscreen : sf::Style::Default };

        m_window.create(m_config.video_mode, m_config.game_name, style);

        m_window.setFramerateLimit(m_config.frame_rate_limit);
        m_window.setKeyRepeatEnabled(false);

        // verify the window size is what was specified/expected,
        // otherwise all the size/positions calculations will be wrong
        const sf::Vector2u windowExpectedSize{ m_config.video_mode.width,
                                               m_config.video_mode.height };

        const sf::Vector2u windowActualSize{ m_window.getSize() };

        std::cout << "Game Window: " << windowExpectedSize << " at "
                  << m_config.video_mode.bitsPerPixel << "bits per pixel and a "
                  << m_config.frame_rate_limit << " fps limit." << std::endl;

        M_CHECK(
            m_window.isOpen(),
            "Failed to make and open the graphics window.  (sf::RenderWindow::isOpen() == false)");

        if (windowActualSize != windowExpectedSize)
        {
            std::cout << "Failed to create a window at " << windowExpectedSize
                      << ", but strangely, a window did open at " << windowActualSize
                      << ".  So...meh." << std::endl;
        }

        m_config.video_mode.width = windowActualSize.x;
        m_config.video_mode.height = windowActualSize.y;
        m_config.video_mode.bitsPerPixel = m_window.getSettings().depthBits;

        m_layout.setupWindow(m_config);

        std::cout << "Game Window Cells: width_ratio=" << m_config.map_cell_size_ratio
                  << ", pixels=" << m_layout.mapCellDimm()
                  << ", grid=" << (m_layout.windowSize() / m_layout.mapCellSize()) << std::endl;
    }

    void GameCoordinator::run(const GameConfig & config)
    {
        initializeSubsystems(config);

        sf::Clock frameClock;
        while (m_window.isOpen() && !m_game.isGameOver())
        {
            handleEvents();
            update(frameClock.restart().asSeconds());
            draw();
            m_stateMachine.changeIfPending(m_context);
        }
    }

    void GameCoordinator::handleEvents()
    {
        sf::Event event;
        while (m_window.isOpen() && !m_game.isGameOver() && m_window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                std::cout << "Player closed the window.  Quitting." << std::endl;
                m_window.close();
                m_stateMachine.setChangePending(State::Teardown);
                return;
            }

            m_stateMachine.state().handleEvent(m_context, event);
        }
    }

    void GameCoordinator::update(const float frameTimeSec)
    {
        m_stateMachine.state().update(m_context, frameTimeSec);
    }

    void GameCoordinator::draw()
    {
        m_window.clear();
        m_stateMachine.state().draw(m_context, m_window, sf::RenderStates());
        m_window.display();
    }

} // namespace castlecrawl
