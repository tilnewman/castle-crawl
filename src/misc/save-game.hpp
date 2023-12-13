#ifndef CASTLECRAWL_SAVE_GAME_HPP_INCLUDED
#define CASTLECRAWL_SAVE_GAME_HPP_INCLUDED
//
// save-game.hpp
//
#include "misc/json.hpp"
#include "map/map-types.hpp"
#include "map/maps.hpp"
#include "misc/player.hpp"

#include <string>

namespace castlecrawl
{
    struct Context;

    struct SaveGame
    {
        Player player;
        MapPos_t player_pos;
        util::FlatMap<std::string, Map> maps;
        std::string map_name;

        void saveToFile(Context & context);
        std::string loadFromFile(Context & context);
    };

    //

    using json = nlohmann::json;

    inline void to_json(json & j, const SaveGame & sg)
    {
        j = json{ { "player", sg.player },
                  { "player_pos", sg.player_pos },
                  { "maps", sg.maps },
                  { "map_name", sg.map_name } };
    }

    inline void from_json(const json & j, SaveGame & sg)
    {
        j.at("player").get_to(sg.player);
        j.at("player_pos").get_to(sg.player_pos);
        j.at("maps").get_to(sg.maps);
        j.at("map_name").get_to(sg.map_name);
    }

} // namespace castlecrawl

#endif // CASTLECRAWL_SAVE_GAME_HPP_INCLUDED
