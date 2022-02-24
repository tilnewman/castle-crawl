// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// editor.cpp
//
#include "editor.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "popup-manager.hpp"
#include "settings.hpp"
#include "state-machine.hpp"
#include "util.hpp"

#include <fstream>

#include <SFML/Graphics/RenderTarget.hpp>

namespace mapper
{

    Editor::Editor()
        : m_position(0, 0)
        , m_defaultMapStrings()
        , m_mapStrings()
        , m_map()
        , m_isFloorStone(false)
        , m_filename()
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

        reset(context);
    }

    void Editor::reset(Context & context)
    {
        m_isFloorStone = false;
        m_position = context.layout.cellCountsMax() / 2;
        m_mapStrings = m_defaultMapStrings;
        updateAndRedraw(context);
    }

    void Editor::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates & states) const
    {
        m_map.draw(context, target, states);

        util::drawRectangleShape(
            target, context.layout.cellBounds(m_position), true, sf::Color(0, 255, 255, 32));
    }

    void Editor::setFloorIsStone(Context & context, const bool isStone)
    {
        m_isFloorStone = isStone;
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
        m_map = Map(context, m_isFloorStone, m_mapStrings, {});
        context.layout.setupBoardForNewMap(m_map.size());
        m_map.load(context);
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

    void Editor::save(Context & context)
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

        context.popup.setup(context, "Saved: " + path.string());
        context.state.setChangePending(State::Popup);
    }

} // namespace mapper
