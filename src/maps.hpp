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

        Map & get() { return *m_currentMapPtr; }
        const Map & get() const { return *m_currentMapPtr; }

        void switchTo(Context & context, const MapLink & link);

        void dumpAllToFile() const;

      private:
        util::FlatMap<std::string, Map> m_maps;
        std::string m_currentMapName;
        Map m_invalidMap;
        Map * m_currentMapPtr;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_MAPS_HPP_INCLUDED
