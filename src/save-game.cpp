// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// save-game.cpp
//
#include "save-game.hpp"

#include "board.hpp"
#include "context.hpp"

#include <fstream>

namespace castlecrawl
{

    void SaveGame::saveToFile(Context & context)
    {
        // gather data
        context.maps.save(context);
        player = context.player;
        player_pos = context.board.player().position();

        // serialize
        json j = *this;

        // save to file
        std::ofstream fileStream("saved-game.txt", std::ios_base::trunc);
        fileStream << std::setw(4) << j;
    }

    void SaveGame::loadFromFile(Context & context)
    {
        // load from file
        std::ifstream fileStream("saved-game.txt", std::ios_base::in);
        json j;
        fileStream >> j;

        // deserialize
        *this = j.get<SaveGame>();

        // distribute data
        context.board.player().position(context, player_pos);
        context.player = player;
        context.maps.load(context);
    }

} // namespace castlecrawl
