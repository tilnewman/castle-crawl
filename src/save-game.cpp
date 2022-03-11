// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// save-game.cpp
//
#include "save-game.hpp"

#include "context.hpp"

#include <fstream>

namespace castlecrawl
{

    void SaveGame::saveToFile(Context & context)
    {
        // serialize
        context.maps.save(context);
        context.save.player = context.player;
        json j = *this;

        // save to file
        std::ofstream fileStream("saved-game.txt", std::ios_base::trunc);
        fileStream << std::setw(4) << j;
    }

} // namespace castlecrawl
