// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// editor.cpp
//
#include "editor.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "layout.hpp"
#include "media.hpp"
#include "popup-manager.hpp"
#include "sound-player.hpp"
#include "state-machine.hpp"
#include "util.hpp"

#include <fstream>

#include <SFML/Graphics/RenderTarget.hpp>

namespace castlecrawl
{

    Editor::Editor()
        : m_position(0, 0)
        , m_defaultMapStrings()
        , m_mapStrings()
        , m_map()
        , m_mapVerts()
        , m_floor(Floor::Stone)
        , m_filename()
        , m_cursorRectangle()
    {}

    void Editor::setup(Context & context)
    {
        // make default map
        const std::string row(static_cast<std::size_t>(context.layout.cellCountsMax().x), '.');
        m_defaultMapStrings.reserve(static_cast<std::size_t>(context.layout.cellCountsMax().y));
        for (int y = 0; y < context.layout.cellCountsMax().y; ++y)
        {
            m_defaultMapStrings.push_back(row);
        }

        m_cursorRectangle.setFillColor(sf::Color(0, 255, 255, 32));
        m_cursorRectangle.setOutlineColor(sf::Color::Cyan);
        m_cursorRectangle.setOutlineThickness(1.0f);
        m_cursorRectangle.setSize(context.layout.cellSize());

        reset(context);
    }

    void Editor::movePosition(Context & context, const MapPos_t & amount)
    {
        context.audio.play("tick-on-1");
        m_position += amount;
        m_cursorRectangle.setPosition(util::position(context.layout.cellBounds(m_position)));
    }

    void Editor::setPosition(Context & context, const MapPos_t & position)
    {
        m_position = position;
        m_cursorRectangle.setPosition(util::position(context.layout.cellBounds(m_position)));
    }

    void Editor::reset(Context & context)
    {
        m_floor = Floor::Stone;
        m_position = context.layout.cellCountsMax() / 2;
        m_mapStrings = m_defaultMapStrings;
        updateAndRedraw(context);
        m_cursorRectangle.setPosition(util::position(context.layout.cellBounds(m_position)));
    }

    void Editor::drawLower(
        const Context & context, sf::RenderTarget & target, sf::RenderStates & states) const
    {
        states.texture = &context.media.tileTexture();

        if (!m_mapVerts.floor.empty())
        {
            target.draw(&m_mapVerts.floor[0], m_mapVerts.floor.size(), sf::Quads, states);
        }

        if (!m_mapVerts.border.empty())
        {
            // do not use states because these verts have no texture only color
            target.draw(&m_mapVerts.border[0], m_mapVerts.border.size(), sf::Quads);
        }
    }

    void Editor::drawUpper(
        const Context & context, sf::RenderTarget & target, sf::RenderStates & states) const
    {
        states.texture = &context.media.tileTexture();

        if (!m_mapVerts.transition.empty())
        {
            target.draw(&m_mapVerts.transition[0], m_mapVerts.transition.size(), sf::Quads, states);
        }

        target.draw(m_cursorRectangle);
    }

    void Editor::setFloor(Context & context, const Floor floor)
    {
        m_floor = floor;
        updateAndRedraw(context);
    }

    void Editor::setCell(Context & context, const char ch)
    {
        m_mapStrings.at(static_cast<std::size_t>(m_position.y))
            .at(static_cast<std::size_t>(m_position.x)) = ch;

        updateAndRedraw(context);
    }

    void Editor::updateAndRedraw(Context & context)
    {
        context.audio.play("tick-off-2");
        m_map = Map(context.random, m_floor, m_mapStrings, {});
        context.layout.calcBoardValues(m_map.size());
        m_mapVerts.reset();
        m_map.load(context, m_mapVerts, {});
    }

    const std::filesystem::path Editor::getFirstAvailableFilePath() const
    {
        int number = 0;
        std::filesystem::path path;
        std::string filename;

        do
        {
            ++number;

            filename = "map-";
            filename += std::to_string(number);
            filename += ".txt";

            path = (std::filesystem::current_path() / filename);
        } while (std::filesystem::exists(path));

        return path;
    }

    bool Editor::canFileBeSaved()
    {
        if (m_filename.empty())
        {
            return false;
        }

        try
        {
            const auto path = (std::filesystem::current_path() / m_filename);
            const bool didFilePreExist = std::filesystem::exists(path);

            {
                std::ofstream stream(path, std::ios_base::out);

                if (!stream.is_open() || !stream.good())
                {
                    return false;
                }
            }

            if (!didFilePreExist)
            {
                std::filesystem::remove(path);
            }
        }
        catch (...)
        {
            return false;
        }

        return true;
    }

    void Editor::save(Context &)
    {
        const auto path = (std::filesystem::current_path() / m_filename);

        {
            std::ofstream stream(path, std::ios_base::trunc);

            if (!stream.is_open() || !stream.good())
            {
                std::cout << "Error:  Can't open file: \"" << path.string() << '\"' << std::endl;
                return;
            }

            for (const std::string & row : m_mapStrings)
            {
                stream << row << '\n';
            }
        }

        std::cout << "Saved: " << path.string() << std::endl;
    }

    bool Editor::load(Context & context, const std::filesystem::path & path)
    {
        if (!std::filesystem::exists(path))
        {
            std::cout << "Error:  Unable to FIND the file: \"" << path.string() << '\"'
                      << std::endl;

            return false;
        }

        m_filename = path.filename().string();

        std::ifstream stream(path, std::ios_base::in);

        if (!stream.is_open() || !stream.good())
        {
            std::cout << "Error:  Unable to OPEN the file: \"" << path.string() << '\"'
                      << std::endl;

            return false;
        }

        m_mapStrings.clear();

        std::string line;
        while (std::getline(stream, line))
        {
            if (line.size() != static_cast<std::size_t>(context.layout.cellCountsMax().x))
            {
                std::cout << "Error:  The file format is invalid.  Lines not all "
                          << context.layout.cellCountsMax().x << " wide.  \"" << path.string()
                          << '\"' << std::endl;

                return false;
            }
            else
            {
                m_mapStrings.push_back(line);
            }
        }

        if (m_mapStrings.size() != static_cast<std::size_t>(context.layout.cellCountsMax().y))
        {
            std::cout << "Error:  The file format is invalid.  " << m_mapStrings.size()
                      << " Lines/rows instead of " << context.layout.cellCountsMax().y << ".  \""
                      << path.string() << '\"' << std::endl;

            return false;
        }

        updateAndRedraw(context);

        return true;
    }

} // namespace castlecrawl
