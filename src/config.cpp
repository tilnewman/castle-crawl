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

} // namespace castlecrawl
