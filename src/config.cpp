// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// config.cpp
//
#include "config.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "map.hpp"
#include "sfml-util.hpp"

#include <iostream>

namespace castlecrawl
{
    GameConfig::GameConfig()
        : media_dir_path{ std::filesystem::current_path() / "media" }
        , video_mode{ sf::VideoMode::getDesktopMode() }
        , frame_rate_limit{ 0 } // leave unlimited while developing
        , background_color{ sf::Color(14, 17, 20) }
        , cell_counts(41, 23) // looks good on wide screens - NEVER CHANGE - maps depend on these
    {}

    void GameConfig::setup(const sf::VideoMode & videoModeActual)
    {
        try
        {
            media_dir_path = std::filesystem::canonical(media_dir_path);
        }
        catch (...)
        {
        }

        M_CHECK(
            std::filesystem::exists(media_dir_path),
            "Error:  The media path does not exist:"
                << media_dir_path
                << "\nPut the media path on the command line or put the 'media' folder here.");

        // sometimes SFML doesn't use the resolution you specify, so set the actual values here
        video_mode = videoModeActual;

        // sometimes SFML repoprts 32bpp as zero, don't know why, don't really care
        if (0 == video_mode.bitsPerPixel)
        {
            video_mode.bitsPerPixel = 32;
        }

        std::cout << "Game Window Resolution: " << video_mode.width << 'x' << video_mode.height
                  << std::endl;
    }

} // namespace castlecrawl
