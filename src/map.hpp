#ifndef CASTLECRAWL_MAP_HPP_INCLUDED
#define CASTLECRAWL_MAP_HPP_INCLUDED
//
// map.hpp
//
#include "map-types.hpp"
#include "random.hpp"

#include <vector>

namespace castlecrawl
{
    struct Context;

    struct MapVerts
    {
        VertVec_t floor;
        VertVec_t border;
        VertVec_t wall;
        VertVec_t transition;

        void reset();
    };

    class Map
    {
      public:
        Map();

        Map(const util::Random & random,
            const bool isFloorStone,
            const MapChars_t &,
            const MapLinks_t &);

        void load(Context & context, MapVerts & verts);
        void updateMapChars(const util::Random & random);

        MapPos_t size() const;
        bool empty() const { return !((size().x > 0) && (size().y > 0)); }

        bool isPosValid(const MapPos_t & pos) const
        {
            return ((pos.x >= 0) && (pos.y >= 0) && (pos.x < size().x) && (pos.y < size().y));
        }

        char getChar(const MapPos_t & pos) const;
        char getChar(const int x, const int y) const { return getChar(MapPos_t{ x, y }); }

        void setChar(const MapPos_t & pos, const char newChar);
        void setChar(const int x, const int y, const char newChar) { setChar({ x, y }, newChar); }

        const MapLinks_t & links() const { return m_links; }

        const MapChars_t & strings() const { return m_chars; }

      private:
        void addWalls();
        void addWallCorners();
        void randomizeFloorTiles(const util::Random & random);
        void resetDoors(Context &);

        static void makeBorderVerts(const Context & context, const MapChars_t &, VertVec_t &);
        void makeStoneTransitionVerts(const Context &, VertVec_t &);
        static void makeVerts(const Context &, const MapChars_t &, VertVec_t &);

      private:
        bool m_isFloorStone;

        MapChars_t m_chars;
        MapChars_t m_floorChars;
        MapLinks_t m_links;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_MAP_HPP_INCLUDED
