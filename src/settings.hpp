#ifndef CASTLECRAWL_SETTINGS_HPP_INCLUDED
#define CASTLECRAWL_SETTINGS_HPP_INCLUDED
//
// settings.hpp
//
#include "map-types.hpp"
#include "tile-image.hpp"

#include <filesystem>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace castlecrawl
{
    class Map;
    struct Context;

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

    // Everything about the window that can only be calculated once BOTH the window is open and the
    // map has been parsed.
    class Layout
    {
      public:
        Layout() = default;

        // always call this first, before setupBoardValues() below
        void calcWindowValues(const GameConfig & config);

        // always call this just before each map::load()
        void calcBoardValues(const sf::Vector2i & mapSize);

        // these are set at startup with resolution and config.cell_counts
        const sf::Vector2f windowSize() const;
        const sf::FloatRect windowBounds() const { return m_windowBounds; }
        float mapCellDimm() const { return m_cellSize.x; }
        const sf::Vector2f mapCellSize() const { return m_cellSize; }
        const sf::FloatRect boardRegion() const { return m_boardRegion; }
        const sf::FloatRect topRegion() const { return m_topRegion; }
        const sf::Vector2f cellSize() const { return m_cellSize; }

        // these change with the map
        const sf::FloatRect boardBounds() const { return m_boardBounds; }
        const sf::Vector2i cellCounts() const { return m_cellCounts; }
        const sf::Vector2i cellCountsMax() const { return { 41, 23 }; }
        const sf::FloatRect cellBounds(const MapPos_t & pos) const;
        bool isPositionValid(const MapPos_t & pos) const;

        const MapPos_t cellPosition(const sf::Vector2f & windowPosition) const;

      protected:
        // these are set at startup with resolution and config.cell_counts
        sf::FloatRect m_windowBounds;
        sf::FloatRect m_boardRegion;
        sf::FloatRect m_topRegion;
        sf::Vector2f m_cellSize;

        // these members change with the map
        sf::FloatRect m_boardBounds;
        sf::Vector2i m_cellCounts;
    };

    // All info about a game in progress that can changes during play.
    class GameInPlay
    {
      public:
        GameInPlay() = default;

        void reset();

        int score() const { return m_score; }
        void score(const int newScore) { m_score = newScore; }
        int scoreAdj(const int adj);

        bool isGameOver() const { return m_isGameOver; }

        void endGame(const bool didPlayerWin)
        {
            m_isGameOver = true;
            m_didPlayerWin = didPlayerWin;
        }

        bool didPlayerWin() const
        {
            if (!m_isGameOver)
            {
                return false;
            }

            return m_didPlayerWin;
        }

      protected:
        int m_score{ 0 };
        bool m_isGameOver{ false };
        bool m_didPlayerWin{ false };
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_SETTINGS_HPP_INCLUDED
