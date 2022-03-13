#ifndef CASTLECRAWL_LAYOUT_HPP_INCLUDED
#define CASTLECRAWL_LAYOUT_HPP_INCLUDED
//
// layout.hpp
//
#include "config.hpp"
#include "map-types.hpp"
#include "tile-image.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace castlecrawl
{
    class Map;
    struct Context;

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

} // namespace castlecrawl

#endif // CASTLECRAWL_LAYOUT_HPP_INCLUDED
