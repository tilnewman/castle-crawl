#ifndef CASTLECRAWL_EDITOR_HPP_INCLUDED
#define CASTLECRAWL_EDITOR_HPP_INCLUDED
//
// editor.hpp
//
#include "map/map-types.hpp"
#include "map/map.hpp"

#include <filesystem>
#include <string>
#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sf
{
    class RenderTarget;
}

namespace castlecrawl
{
    struct Context;

    struct MapEntry_t
    {
        MapPos_t pos;
        sf::FloatRect rect;
    };

    class Editor
    {
      public:
        Editor();
        void setup(Context & context);
        void reset(Context & context);

        void drawLower(
            const Context & context, sf::RenderTarget & target, sf::RenderStates & states) const;

        void drawUpper(
            const Context & context, sf::RenderTarget & target, sf::RenderStates & states) const;

        void setCell(Context & context, const char ch);

        void setFilename(const std::string & filename) { m_filename = filename; }
        const std::string getFilename() const { return m_filename; }

        void changeFloor(Context & context);

        const MapPos_t position() const { return m_position; }
        void movePosition(Context & context, const MapPos_t & amount);
        void setPosition(Context & context, const MapPos_t & position);

        const std::filesystem::path getFirstAvailableFilePath() const;

        bool canFileBeSaved();
        void save(Context & context);
        bool load(Context & context, const std::filesystem::path & path);

        void showHelpText(Context & context);
        void hideHelpText() { m_helpText.setString(""); }

        void startFadeText(Context & context, const std::string & message);
        void updateFadeText();

        bool isDragging() const { return m_isDragging; }
        void startDragging(Context & context, const sf::Vector2f & pos);
        void stopDragging(Context & context, const sf::Vector2f & pos);
        void updateDragging(Context & context, const sf::Vector2f & pos);

      private:
        void updateDragRect();
        void updateDragSelectedMapCells(Context & context);
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
        sf::Text m_helpText;
        bool m_isDragging;
        sf::Vector2f m_dragPosStart;
        sf::Vector2f m_dragPosStop;
        sf::RectangleShape m_dragRectangle;
        std::vector<MapEntry_t> m_dragSelectedEntrys;
        sf::Text m_fadeText;
    };
} // namespace castlecrawl

#endif // CASTLECRAWL_EDITOR_HPP_INCLUDED
