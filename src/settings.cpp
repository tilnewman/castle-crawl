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
#include <iostream>

namespace castlecrawl
{
    GameConfig::GameConfig()
        : media_dir_path{ std::filesystem::current_path() / "media" }
        , video_mode{ sf::VideoMode::getDesktopMode() }
        , frame_rate_limit{ 0 }
        , background_color{ sf::Color(14, 17, 20) }
        , cell_counts(41, 23) // these values just look good, not too big, not too small
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
    }

    const sf::Vector2f Layout::windowSize() const { return util::size(m_windowBounds); }

    void Layout::calcWindowValues(const GameConfig & config)
    {
        const sf::Vector2f windowSize{ sf::Vector2u{ config.video_mode.width,
                                                     config.video_mode.height } };

        m_windowBounds = sf::FloatRect({ 0.0f, 0.0f }, windowSize);

        int cellDimm = (static_cast<int>(windowSize.x) / config.cell_counts.x);

        // keep seeing drawing artifacts if this is odd, so make sure it is even
        util::makeEven(cellDimm, false);

        m_cellSize = sf::Vector2f{ sf::Vector2i{ cellDimm, cellDimm } };

        const sf::Vector2f boardRegionSize = (m_cellSize * sf::Vector2f{ config.cell_counts });

        m_topRegion = { { 0.0f, 0.0f },
                        { windowSize.x, (windowSize.y - boardRegionSize.y) - 2.0f } };

        m_boardRegion = { { ((windowSize.x * 0.5f) - (boardRegionSize.x * 0.5f)),
                            (m_topRegion.height + 1.0f) },
                          boardRegionSize };
    }

    void Layout::calcBoardValues(const sf::Vector2i & mapSize)
    {
        m_cellCounts = mapSize;

        const sf::Vector2f boardSize{ sf::Vector2i(m_cellSize) * m_cellCounts };
        const sf::Vector2f boardPos{ util::center(m_boardRegion) - (boardSize / 2.0f) };
        m_boardBounds = sf::FloatRect(boardPos, boardSize);
    }

    bool Layout::isPositionValid(const MapPos_t & pos) const
    {
        return (
            (pos.x >= 0) && (pos.x < m_cellCounts.x) && (pos.y >= 0) && (pos.y < m_cellCounts.y));
    }

    const sf::FloatRect Layout::cellBounds(const MapPos_t & pos) const
    {
        const sf::FloatRect bounds{
            (util::position(m_boardBounds) + (m_cellSize * sf::Vector2f(pos))), m_cellSize
        };

        return bounds;
    }

    const MapPos_t Layout::cellPosition(const sf::Vector2f & windowPosition) const
    {
        for (int y = 0; y < m_cellCounts.y; ++y)
        {
            for (int x = 0; x < m_cellCounts.x; ++x)
            {
                if (cellBounds({ x, y }).contains(windowPosition))
                {
                    return { x, y };
                }
            }
        }

        return { -1, -1 };
    }

    //

    void GameInPlay::reset()
    {
        m_score = 0;
        m_isGameOver = false;
        m_didPlayerWin = false;
    }

    int GameInPlay::scoreAdj(const int adj)
    {
        m_score += adj;

        if (m_score < 0)
        {
            m_score = 0;
        }

        return m_score;
    }
} // namespace castlecrawl
