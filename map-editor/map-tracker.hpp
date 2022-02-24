#ifndef CASTLECRAWLMAPPER_MAP_TRACKER_HPP_INCLUDED
#define CASTLECRAWLMAPPER_MAP_TRACKER_HPP_INCLUDED
//
// map-tracker.hpp
//
#include "map.hpp"

#include <memory>

namespace mapper
{

    class MapTracker
    {
      public:
      private:
        std::unique_ptr<Map> m_mapUPtr;
    };
} // namespace mapper

#endif // CASTLECRAWLMAPPER_MAP_TRACKER_HPP_INCLUDED
