#ifndef CASTLECRAWLMAPPER_EDITOR_HPP_INCLUDED
#define CASTLECRAWLMAPPER_EDITOR_HPP_INCLUDED
//
// map-tracker.hpp
//
#include "map-types.hpp"
#include "map.hpp"

namespace mapper
{

    class Editor
    {
      public:
      private:
        MapPos_t m_position;
        MapChars_t m_map;
    };
} // namespace mapper

#endif // CASTLECRAWLMAPPER_EDITOR_HPP_INCLUDED
