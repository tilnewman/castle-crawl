// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// game-coordinator.cpp
//
#include "game-coordinator.hpp"

#include "check-macros.hpp"
#include "util.hpp"

#include <algorithm>
#include <filesystem>
#include <iostream>

#include <SFML/Graphics.hpp>

namespace mapper
{
    GameCoordinator::GameCoordinator()
        : m_window()
        , m_renderStates()
        , m_media()
        , m_board()
        , m_layout()
        , m_editor()
        , m_map()
        , m_config()
        , m_state()
        , m_popup()
        , m_random()
        , m_context(
              m_board, m_map, m_editor, m_config, m_layout, m_media, m_state, m_popup, m_random)
    {}

    bool GameCoordinator::setup(const GameConfig & configOrig)
    {
        m_config = configOrig;
        M_CHECK(std::filesystem::exists(m_config.media_dir_path), m_config.media_dir_path);
        M_CHECK(std::filesystem::is_directory(m_config.media_dir_path), m_config.media_dir_path);

        openWindow();

        m_window.setFramerateLimit(m_config.frame_rate_limit);
        m_window.setKeyRepeatEnabled(false);

        m_config.video_mode.width = m_window.getSize().x;
        m_config.video_mode.height = m_window.getSize().y;
        m_config.video_mode.bitsPerPixel = m_window.getSettings().depthBits;

        // sometimes SFML reports 32bpp as zero for some reason...meh
        if (0 == m_config.video_mode.bitsPerPixel)
        {
            m_config.video_mode.bitsPerPixel = 32;
        }

        m_layout.setupWindowInitial(m_config);

        m_media.load(m_config, m_layout);

        m_editor.setup(m_context);

        // establish which file we will be creating
        const auto path = m_editor.getFirstAvailableFilePath();
        m_editor.setFilename(path.filename().string());
        if (!m_editor.canFileBeSaved())
        {
            std::cout << "Error:  Unable open/write/save/whatever the file: \"" << path.string()
                      << "\"\nThere is probably a strange unicode character in the path or a "
                         "permissions problem.  Try running this editor in a different location."
                      << std::endl;

            return false;
        }

        m_popup.setup(m_context, path.string());
        m_state.setChangePending(State::Popup);

        std::cout << "Press F1 for help, Escape to quit." << std::endl;
        return true;
    }

    void GameCoordinator::openWindow()
    {
        m_window.close();

        const auto style{ (m_config.is_fullscreen) ? sf::Style::Fullscreen : sf::Style::Default };

        m_window.create(m_config.video_mode, m_config.game_name, style);

        // verify the window size is what was specified/expected,
        // otherwise all the size/positions calculations will be wrong
        const sf::Vector2u windowExpectedSize{ m_config.video_mode.width,
                                               m_config.video_mode.height };

        const sf::Vector2u windowActualSize{ m_window.getSize() };

        M_CHECK(
            m_window.isOpen(),
            "Failed to make and open the graphics window.  (sf::RenderWindow::isOpen() == false)");

        if (windowActualSize != windowExpectedSize)
        {
            std::cout << "Failed to create a window at " << windowExpectedSize
                      << ", but strangely, a window did open at " << windowActualSize
                      << ".  So...meh." << std::endl;
        }
    }

    void GameCoordinator::run(const GameConfig & config)
    {
        if (!setup(config))
        {
            return;
        }

        sf::Clock frameClock;
        while (m_window.isOpen() && (m_state.which() != State::Teardown))
        {
            handleEvents();
            update(frameClock.restart().asSeconds());
            draw();
            m_state.changeIfPending(m_context);
        }
    }

    void GameCoordinator::handleEvents()
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                std::cout << "User closed the window.  Quitting." << std::endl;
                m_window.close();
                m_state.setChangePending(State::Teardown);
                return;
            }

            m_state.state().handleEvent(m_context, event);
        }
    }

    void GameCoordinator::update(const float frameTimeSec)
    {
        m_state.state().update(m_context, frameTimeSec);
    }

    void GameCoordinator::draw()
    {
        m_window.clear(m_config.background_color);
        m_state.state().draw(m_context, m_window, m_renderStates);
        m_window.display();
    }

} // namespace mapper
