// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// editor.cpp
//
#include "state/editor.hpp"

#include "audio/sound-player.hpp"
#include "display/layout.hpp"
#include "display/media.hpp"
#include "display/popup-manager.hpp"
#include "misc/check-macros.hpp"
#include "misc/context.hpp"
#include "misc/sfml-util.hpp"
#include "state/state-machine.hpp"

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
        , m_helpText()
        , m_isDragging(false)
        , m_dragPosStart(0.0f, 0.0f)
        , m_dragPosStop(0.0f, 0.0f)
        , m_dragRectangle()
        , m_dragSelectedEntrys()
    {}

    void Editor::setup(Context & context)
    {
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

        m_dragRectangle.setFillColor(sf::Color(0, 255, 255, 64));
        m_dragRectangle.setOutlineThickness(0.0f);

        m_helpText = context.media.makeText(FontSize::Small, "");

        m_fadeText = context.media.makeText(FontSize::Large, "");
        m_fadeText.setFillColor(sf::Color::Transparent);

        reset(context);
    }

    void Editor::movePosition(Context & context, const MapPos_t & amount)
    {
        context.audio.play("tick-on-1");
        m_position += amount;
        m_cursorRectangle.setPosition(util::position(context.layout.cellBounds(m_position)));
        m_dragSelectedEntrys.clear();
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

        if (m_isDragging)
        {
            target.draw(m_dragRectangle);
        }

        for (const MapEntry_t & entry : m_dragSelectedEntrys)
        {
            sf::RectangleShape rectangle;
            rectangle.setFillColor(sf::Color(0, 255, 255, 64));
            rectangle.setPosition(util::position(entry.rect));
            rectangle.setSize(util::size(entry.rect));

            target.draw(rectangle);
        }

        if (!m_helpText.getString().isEmpty())
        {
            target.draw(m_helpText);
        }

        target.draw(m_fadeText);
    }

    void Editor::setFloor(Context & context, const Floor floor)
    {
        m_floor = floor;
        updateAndRedraw(context);
    }

    void Editor::setCell(Context & context, const char ch)
    {
        if (m_dragSelectedEntrys.empty())
        {
            m_mapStrings.at(static_cast<std::size_t>(m_position.y))
                .at(static_cast<std::size_t>(m_position.x)) = ch;
        }
        else
        {
            for (const MapEntry_t & entry : m_dragSelectedEntrys)
            {
                m_mapStrings.at(static_cast<std::size_t>(entry.pos.y))
                    .at(static_cast<std::size_t>(entry.pos.x)) = ch;
            }
        }

        // clang-format off
        switch (ch)
        {
            case 'a': { startFadeText("Slime"); break; }
            case 'l': { startFadeText("Lave"); break; }
            case 'w': { startFadeText("Water"); break; }
            case '.': { startFadeText("Erase"); break; }
            case ' ': { startFadeText("Bare Floor"); break; }
            case 'b': { startFadeText("Barrel"); break; }
            case 'c': { startFadeText("Chest"); break; }
            case 'k': { startFadeText("Coffin"); break; }
            case 'r': { startFadeText("Rock Wall"); break; }
            case 'S': { startFadeText("Stairs Up"); break; }
            case 's': { startFadeText("Staris Down"); break; }
            case 'D': { startFadeText("Door Locked"); break; }
            case 'd': { startFadeText("Door Unlocked"); break; }
            default: { break; }
        }
        // clang-format on

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

    void Editor::showHelpText(Context & context)
    {
        const std::string helpMessage(
            "Esc-Quit\nCNTRL-s-Save\nSpace-Bare Floor\nPeriod-Erase\n"
            "1-Dirt Floor\n2-Stone Floor\n3-Wood Floor\na-Bag\n"
            "r-Rock\nl-Lava\nw-Water\ng-Slime\nc-Chest\nk-Coffin\n"
            "S-Stairs Up\ns-Stair Down\nD-Door Locked\nd-Door Unlocked\n");

        m_helpText.setString(helpMessage);

        m_helpText.setPosition(
            ((context.layout.topRegion().width * 0.5f) -
             (m_helpText.getGlobalBounds().width * 0.5f)),
            50.0f);
    }

    void Editor::startFadeText(const std::string & message)
    {
        m_helpText.setString(message);
        m_helpText.setFillColor(sf::Color::White);
    }

    void Editor::updateFadeText()
    {
        sf::Color color = m_helpText.getFillColor();
        if (color.a > 0)
        {
            --color.a;
            m_helpText.setFillColor(color);
        }
    }

    void Editor::startDragging(Context & context, const sf::Vector2f & pos)
    {
        m_dragPosStart = pos;
        m_dragPosStop = pos;

        updateDragRect();

        m_isDragging = context.layout.boardBounds().contains(pos);

        updateDragSelectedMapCells(context);

        context.audio.play("tick-on-1");
    }

    void Editor::stopDragging(Context & context, const sf::Vector2f & pos)
    {
        const MapPos_t newMapPos = context.layout.cellPosition(pos);

        if (context.layout.isPositionValid(newMapPos))
        {
            setPosition(context, newMapPos);
            context.audio.play("tick-off-1");
        }

        m_isDragging = false;

        if (context.layout.boardBounds().contains(pos))
        {
            updateDragRect();
        }
        else
        {
            m_dragRectangle.setPosition({ 0.0f, 0.0f });
            m_dragRectangle.setSize({ 0.0f, 0.0f });
        }
    }

    void Editor::updateDragging(Context & context, const sf::Vector2f & pos)
    {
        m_dragPosStop = pos;
        updateDragRect();
        updateDragSelectedMapCells(context);
    }

    void Editor::updateDragRect()
    {
        m_dragRectangle.setPosition(
            util::min(m_dragPosStart.x, m_dragPosStop.x),
            util::min(m_dragPosStart.y, m_dragPosStop.y));

        m_dragRectangle.setSize(sf::Vector2f{ util::abs(m_dragPosStart.x - m_dragPosStop.x),
                                              util::abs(m_dragPosStart.y - m_dragPosStop.y) });
    }

    void Editor::updateDragSelectedMapCells(Context & context)
    {
        m_dragSelectedEntrys.clear();

        const sf::FloatRect mapRect = context.layout.boardBounds();
        const sf::Vector2i mapSize = context.layout.cellCounts();

        sf::Vector2f screenPos = util::position(mapRect);
        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                const sf::FloatRect screenRect{ screenPos, context.layout.cellSize() };

                const sf::FloatRect dragRect{ util::position(m_dragRectangle),
                                              util::size(m_dragRectangle) };

                if (screenRect.intersects(dragRect))
                {
                    const MapEntry_t entry{ { x, y }, screenRect };
                    m_dragSelectedEntrys.push_back(entry);
                }

                screenPos.x += context.layout.cellSize().x;
            }

            screenPos.x = mapRect.left;
            screenPos.y += context.layout.cellSize().y;
        }
    }

} // namespace castlecrawl
