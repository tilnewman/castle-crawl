#ifndef CASTLECRAWL_SAVE_GAME_HPP_INCLUDED
#define CASTLECRAWL_SAVE_GAME_HPP_INCLUDED
//
// save-game.hpp
//
#include "json.hpp"
#include "maps.hpp"
#include "player.hpp"

namespace castlecrawl
{
    struct Context;

    struct SaveGame
    {
        Player player;
        util::FlatMap<std::string, Map> maps;
        std::string map_name;

        void saveToFile(Context & context);
    };

    //

    using json = nlohmann::json;

    inline void to_json(json & j, const SaveGame & sg)
    {
        j = json{ { "player", sg.player }, { "maps", sg.maps }, { "map_name", sg.map_name } };
    }

    inline void from_json(const json & j, SaveGame & sg)
    {
        j.at("player").get_to(sg.player);
        j.at("maps").get_to(sg.maps);
        j.at("map_name").get_to(sg.map_name);
    }

} // namespace castlecrawl

#endif // CASTLECRAWL_SAVE_GAME_HPP_INCLUDED
