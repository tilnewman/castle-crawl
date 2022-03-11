#ifndef CASTLECRAWL_MAP_HPP_INCLUDED
#define CASTLECRAWL_MAP_HPP_INCLUDED
//
// map.hpp
//
#include "json.hpp"
#include "map-types.hpp"
#include "random.hpp"

#include <vector>

namespace castlecrawl
{
    using json = nlohmann::json;

    struct Context;

    struct MapVerts
    {
        VertVec_t floor;
        VertVec_t border;
        VertVec_t transition;

        void reset();
    };

    enum class Floor
    {
        Wood,
        Stone,
        Dirt
    };

    //

    class Map
    {
      public:
        Map();

        Map(const util::Random & random, const Floor floor, const MapChars_t &, const MapLinks_t &);

        void load(Context & context, MapVerts & verts, const MapPos_t playerPos);

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

        const std::vector<char> charsAround(const MapPos_t & pos) const;
        std::size_t countCharsAround(const MapPos_t & pos, const char ch) const;

      private:
        void convertMapChars(const util::Random & random);

        void convertWalls();
        void convertWallCorners();
        void randomizeFloorTiles(const util::Random & random);
        void resetPieces(Context & context, const MapPos_t playerPos);

        static void makeBorderVerts(const Context & context, const MapChars_t &, VertVec_t &);
        void makeStoneTransitionVerts(const Context &, VertVec_t &);
        static void makeVerts(const Context &, const MapChars_t &, VertVec_t &);

        friend void to_json(json & j, const Map & m);
        friend void from_json(const json & j, Map & m);

      private:
        Floor m_floor;
        MapChars_t m_chars;
        MapChars_t m_floorChars;
        MapLinks_t m_links;
    };

    inline void to_json(json & j, const Map & m)
    {
        j = json{ { "floor", m.m_floor },
                  { "chars", m.m_chars },
                  { "floor_chars", m.m_floorChars },
                  { "links", m.m_links } };
    }

    inline void from_json(const json & j, Map & m)
    {
        j.at("floor").get_to(m.m_floor);
        j.at("chars").get_to(m.m_chars);
        j.at("floor_chars").get_to(m.m_floorChars);
        j.at("links").get_to(m.m_links);
    }

} // namespace castlecrawl

#endif // CASTLECRAWL_MAP_HPP_INCLUDED
