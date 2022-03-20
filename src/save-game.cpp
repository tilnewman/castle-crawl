// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// save-game.cpp
//
#include "save-game.hpp"

#include "board.hpp"
#include "context.hpp"

#include <filesystem>
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

    std::string SaveGame::loadFromFile(Context & context)
    {
        try
        {
            // check that file exists
            const std::filesystem::path path{ "saved-game.txt" };
            if (!std::filesystem::exists(path))
            {
                throw std::runtime_error("Error:  No saved game to load!");
            }

            // open file
            std::ifstream fileStream(path.string(), std::ios_base::in);
            if (!fileStream.good())
            {
                throw std::runtime_error("Error:  Unable to open saved game file!");
            }

            try
            {
                // load from file
                json j;
                fileStream >> j;

                // deserialize
                *this = j.get<SaveGame>();
            }
            catch (...)
            {
                throw std::runtime_error("Error:  Saved game file contains errors!");
            }

            // distribute data
            context.board.player().position(context, player_pos);
            context.player = player;
            context.maps.load(context);

            return "";
        }
        catch (const std::exception & ex)
        {
            return ex.what();
        }
    }

} // namespace castlecrawl
