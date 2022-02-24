// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// editor.cpp
//
#include "editor.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "settings.hpp"
#include "util.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace mapper
{

    Editor::Editor()
        : m_position(0, 0)
        , m_defaultMapStrings()
        , m_mapStrings()
        , m_map()
        , m_isFloorStone(false)
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
        m_position = { 0, 0 };
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

    void Editor::set(Context & context, const char ch)
    {
        m_mapStrings.at(m_position.y).at(m_position.x) = ch;
        updateAndRedraw(context);
    }

    void Editor::updateAndRedraw(Context & context)
    {
        m_map = Map(context, m_isFloorStone, m_mapStrings, {});
        context.layout.setupBoardForNewMap(m_map.size());
        m_map.load(context);
    }

} // namespace mapper
