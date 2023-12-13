#ifndef CASTLECRAWL_MAPTYPES_HPP_INCLUDED
#define CASTLECRAWL_MAPTYPES_HPP_INCLUDED
//
// map-types.hpp
//
#include "misc/json.hpp"

#include <string>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Vertex.hpp>

namespace sf
{
    using json = nlohmann::json;

    template <typename T>
    inline void to_json(json & j, const Vector2<T> & v)
    {
        j = json{ { "x", v.x }, { "y", v.y } };
    }

    template <typename T>
    inline void from_json(const json & j, Vector2<T> & v)
    {
        j.at("x").get_to(v.x);
        j.at("y").get_to(v.y);
    }

} // namespace sf

namespace castlecrawl
{
    using MapPos_t = sf::Vector2i;
    using MapChars_t = std::vector<std::string>;

    struct MapLink
    {
        MapLink(
            const MapPos_t & fromPos = { 0, 0 },
            const std::string & toName = "",
            const MapPos_t & toPos = { 0, 0 })
            : from_pos(fromPos)
            , to_name(toName)
            , to_pos(toPos)
        {}

        MapPos_t from_pos;
        std::string to_name;
        MapPos_t to_pos;
    };

    using json = nlohmann::json;

    inline void to_json(json & j, const MapLink & ml)
    {
        j = json{ { "from_pos", ml.from_pos }, { "to_name", ml.to_name }, { "to_pos", ml.to_pos } };
    }

    inline void from_json(const json & j, MapLink & ml)
    {
        j.at("from_pos").get_to(ml.from_pos);
        j.at("to_name").get_to(ml.to_name);
        j.at("to_pos").get_to(ml.to_pos);
    }

    using MapLinks_t = std::vector<MapLink>;

    using VertVec_t = std::vector<sf::Vertex>;
} // namespace castlecrawl

#endif // CASTLECRAWL_MAPTYPES_HPP_INCLUDED
