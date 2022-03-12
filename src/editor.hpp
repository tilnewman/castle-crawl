#ifndef CASTLECRAWL_EDITOR_HPP_INCLUDED
#define CASTLECRAWL_EDITOR_HPP_INCLUDED
//
// editor.hpp
//
#include "map-types.hpp"
#include "map.hpp"

#include <filesystem>
#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace sf
{
    class RenderTarget;
}

namespace castlecrawl
{
    struct Context;

    class Editor
    {
      public:
        Editor();
        void setup(Context & context);
        void reset(Context & context);

        void draw(
            const Context & context, sf::RenderTarget & target, sf::RenderStates & states) const;

        void setCell(Context & context, const char ch);

        void setFilename(const std::string & filename) { m_filename = filename; }
        const std::string getFilename() const { return m_filename; }

        void setFloor(Context & context, const Floor floor);
        Floor getFloor() const { return m_floor; }

        const MapPos_t position() const { return m_position; }
        void movePosition(Context & context, const MapPos_t & amount);
        void setPosition(Context & context, const MapPos_t & position);

        const std::filesystem::path getFirstAvailableFilePath() const;

        bool canFileBeSaved();
        void save(Context & context);
        bool load(Context & context, const std::filesystem::path & path);

      private:
        void updateAndRedraw(Context & context);

      private:
        MapPos_t m_position;
        MapChars_t m_defaultMapStrings;
        MapChars_t m_mapStrings;
        Map m_map;
        MapVerts m_mapVerts;
        Floor m_floor;
        std::string m_filename;
        sf::RectangleShape m_cursorRectangle;
    };
} // namespace castlecrawl

#endif // CASTLECRAWL_EDITOR_HPP_INCLUDED
