#ifndef CASTLECRAWL_MAPS_HPP_INCLUDED
#define CASTLECRAWL_MAPS_HPP_INCLUDED
//
// maps.hpp
//
#include "flat-map.hpp"
#include "map.hpp"

#include <string>

namespace castlecrawl
{

    class Maps
    {
      public:
        Maps();

        void loadAll(const util::Random & random);

        Map & get() { return m_maps[m_currentMapName]; }

        const Map & get() const;

        void switchTo(Context & context, const MapLink & link);

      private:
        util::FlatMap<std::string, Map> m_maps;
        std::string m_currentMapName;
        Map m_invalidMap;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_MAPS_HPP_INCLUDED
