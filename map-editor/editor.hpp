#ifndef CASTLECRAWLMAPPER_EDITOR_HPP_INCLUDED
#define CASTLECRAWLMAPPER_EDITOR_HPP_INCLUDED
//
// map-tracker.hpp
//
#include "map-types.hpp"
#include "map.hpp"

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

        void draw(
            const Context & context, sf::RenderTarget & target, sf::RenderStates & states) const;

        const MapPos_t position() const { return m_position; }
        void movePosition(const MapPos_t & amount) { m_position += amount; }

      private:
        MapPos_t m_position;
        MapChars_t m_defaultMapStrings;
        MapChars_t m_mapStrings;
        Map m_map;
    };
} // namespace mapper

#endif // CASTLECRAWLMAPPER_EDITOR_HPP_INCLUDED
