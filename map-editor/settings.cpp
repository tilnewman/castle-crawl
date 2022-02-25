// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// settings.cpp
//
#include "settings.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "map.hpp"
#include "util.hpp"

#include <filesystem>

namespace mapper
{
    GameConfig::GameConfig()
        : game_name{ "game" }
        , media_dir_path{ std::filesystem::current_path() / "media" }
        , video_mode{ sf::VideoMode::getDesktopMode() }
        , is_fullscreen{ true }
        , frame_rate_limit{ 60 }
        , background_color{ sf::Color(14, 14, 17) }
        , map_cell_size_ratio{ 0.024f }
    {}

    sf::Vector2f Layout::windowSize() const { return util::size(m_windowBounds); }

    void Layout::setupWindowInitial(const GameConfig & config)
    {
        const sf::Vector2f windowSize{ sf::Vector2u{ config.video_mode.width,
                                                     config.video_mode.height } };

        m_windowBounds = sf::FloatRect({ 0.0f, 0.0f }, windowSize);

        const float cellDimm = std::floor(config.map_cell_size_ratio * windowSize.x);

        m_cellSize.x = cellDimm;
        m_cellSize.y = cellDimm;
    }

    void Layout::setupBoardForNewMap(const sf::Vector2i & mapSize)
    {
        m_cellCounts = mapSize;

        m_cellCountTotal = static_cast<std::size_t>(m_cellCounts.x * m_cellCounts.y);

        const sf::Vector2f actualBoardSize{ sf::Vector2i(m_cellSize) * m_cellCounts };

        const sf::Vector2f actualBoardPos{ util::center(m_windowBounds) -
                                           (actualBoardSize / 2.0f) };

        m_boardBounds = sf::FloatRect(actualBoardPos, actualBoardSize);
    }

    bool Layout::isPositionValid(const MapPos_t & pos) const
    {
        return (
            (pos.x >= 0) && (pos.x < m_cellCounts.x) && (pos.y >= 0) && (pos.y < m_cellCounts.y));
    }

    sf::FloatRect Layout::cellBounds(const MapPos_t & pos) const
    {
        M_CHECK(isPositionValid(pos), pos);

        const sf::FloatRect bounds{
            (util::position(m_boardBounds) + (m_cellSize * sf::Vector2f(pos))), m_cellSize
        };

        return bounds;
    }

    const MapPos_t Layout::cellIndex(const sf::Vector2f & position) const
    {
        for (int y = 0; y < cellCountsMax().y; ++y)
        {
            for (int x = 0; x < cellCountsMax().x; ++x)
            {
                const sf::FloatRect bounds = cellBounds({ x, y });
                if (bounds.contains(position))
                {
                    return { x, y };
                }
            }
        }

        return { -1, -1 };
    }

} // namespace mapper
