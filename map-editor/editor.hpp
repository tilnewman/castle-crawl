#ifndef CASTLECRAWLMAPPER_EDITOR_HPP_INCLUDED
#define CASTLECRAWLMAPPER_EDITOR_HPP_INCLUDED
//
// map-tracker.hpp
//
#include "map-types.hpp"
#include "map.hpp"

#include <filesystem>
#include <string>

#include <SFML/Graphics/RenderStates.hpp>

namespace sf
{
    class RenderTarget;
}

namespace mapper
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

        void setFloorIsStone(Context & context, const bool isStone);
        bool getFloorIsStone() const { return m_isFloorStone; }

        const MapPos_t position() const { return m_position; }
        void movePosition(const MapPos_t & amount) { m_position += amount; }

        const std::filesystem::path getFirstAvailableFilePath() const;

        bool canFileBeSaved();
        void save(Context & context);

      private:
        void updateAndRedraw(Context & context);

      private:
        MapPos_t m_position;
        MapChars_t m_defaultMapStrings;
        MapChars_t m_mapStrings;
        Map m_map;
        bool m_isFloorStone;
        std::string m_filename;
    };
} // namespace mapper

#endif // CASTLECRAWLMAPPER_EDITOR_HPP_INCLUDED
