#ifndef CASTLECRAWLMAPPER_SETTINGS_HPP_INCLUDED
#define CASTLECRAWLMAPPER_SETTINGS_HPP_INCLUDED
//
// settings.hpp
//
#include "context.hpp"
#include "map-types.hpp"
#include "tile-image.hpp"

#include <filesystem>
#include <string>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace mapper
{
    class Map;

    // All settings about the game that must be set before...well before everything else.
    // No need for an interface class since this will be const in Context.
    struct GameConfig
    {
        GameConfig();

        std::string game_name;
        std::filesystem::path media_dir_path;
        sf::VideoMode video_mode;
        bool is_fullscreen;
        unsigned frame_rate_limit;
        sf::Color background_color;
        float map_cell_size_ratio;
    };

    // Everything about the window that can only be calculated once BOTH the window is open AND the
    // map has been parsed.
    class Layout
    {
      public:
        Layout() = default;

        // always call this setup first on app init
        void setupWindowInitial(const GameConfig & config);

        //...and this setup on each map load
        void setupBoardForNewMap(const sf::Vector2i & mapSize);

        float mapCellDimm() const { return m_cellSize.x; }

        sf::Vector2f mapCellSize() const { return m_cellSize; }

        sf::Vector2f windowSize() const;
        sf::FloatRect windowBounds() const { return m_windowBounds; }
        sf::FloatRect boardBounds() const { return m_boardBounds; }
        sf::Vector2i cellCounts() const { return m_cellCounts; }
        sf::Vector2i cellCountsMax() const { return { 41, 23 }; }
        std::size_t cellCountTotal() const { return m_cellCountTotal; }
        sf::Vector2f cellSize() const { return m_cellSize; }
        sf::FloatRect cellBounds(const MapPos_t & pos) const;

        bool isPositionValid(const MapPos_t & pos) const;

        const MapPos_t cellIndex(const sf::Vector2f & position) const;

      protected:
        sf::FloatRect m_windowBounds;
        sf::FloatRect m_boardBounds;
        sf::Vector2i m_cellCounts;
        std::size_t m_cellCountTotal{ 0 };
        sf::Vector2f m_cellSize;
    };

} // namespace mapper

#endif // CASTLECRAWLMAPPER_SETTINGS_HPP_INCLUDED
