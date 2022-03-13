#ifndef CASTLECRAWL_CONFIG_HPP_INCLUDED
#define CASTLECRAWL_CONFIG_HPP_INCLUDED
//
// config.hpp
//
#include <filesystem>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace castlecrawl
{

    // All settings about the game that must be set before...well before everything else.
    // No need for an interface class since this will be const in Context.
    struct GameConfig
    {
        GameConfig();

        void setup(const sf::VideoMode & videoModeActual);

        std::filesystem::path media_dir_path;
        sf::VideoMode video_mode;
        unsigned frame_rate_limit;
        sf::Color background_color;
        sf::Vector2i cell_counts;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_SETTINGS_HPP_INCLUDED
