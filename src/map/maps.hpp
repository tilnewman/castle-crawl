#ifndef CASTLECRAWL_MAPS_HPP_INCLUDED
#define CASTLECRAWL_MAPS_HPP_INCLUDED
//
// maps.hpp
//
#include "misc/flat-map.hpp"
#include "map/map.hpp"

#include <string>

#include <SFML/Graphics/RenderStates.hpp>

namespace sf
{
    class RenderTarget;
} // namespace sf

namespace castlecrawl
{
    struct Context;
    struct SaveGame;

    class Maps
    {
      public:
        Maps();

        void loadAll(const util::Random & random);

        Map & get() { return *m_currentMapPtr; }
        const Map & get() const { return *m_currentMapPtr; }

        const std::string getName() const { return m_currentMapName; }

        void switchTo(Context & context, const MapLink & link);

        void reloadAfterChange(Context & context);

        void drawLower(
            const Context & context, sf::RenderTarget & target, sf::RenderStates states) const;

        void drawUpper(
            const Context & context, sf::RenderTarget & target, sf::RenderStates states) const;

        void dumpAllToFile() const;

        void save(Context & context) const;
        void load(Context & context);

      private:
        util::FlatMap<std::string, Map> m_maps;
        std::string m_currentMapName;
        Map m_invalidMap;
        Map * m_currentMapPtr;
        MapVerts m_verts;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_MAPS_HPP_INCLUDED
