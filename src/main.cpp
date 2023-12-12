// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// main.cpp
//
#include "check-macros.hpp"
#include "game-coordinator.hpp"
#include "layout.hpp"

#include <cstddef>
#include <filesystem>

int main(const int argc, const char * const argv[])
{

    using namespace castlecrawl;

    try
    {
        GameConfig config;

        if (argc > 1)
        {
            config.media_dir_path =
                std::filesystem::current_path() / std::filesystem::path{ argv[1] };
        }

        try
        {
            config.media_dir_path = std::filesystem::canonical(config.media_dir_path);
        }
        catch (...)
        {
        }

        M_CHECK(
            std::filesystem::exists(config.media_dir_path),
            "Error:  The media path does not exist:"
                << config.media_dir_path
                << "\nPut the media path on the command line or put the 'media' folder here.");

        config.video_mode.width = 1920;
        config.video_mode.height = 1200;
        config.video_mode.bitsPerPixel = sf::VideoMode::getDesktopMode().bitsPerPixel;

        // sometimes the getDesktopMode().bitsPerPixel is zero when it should be 32?!
        if (0 == config.video_mode.bitsPerPixel)
        {
            config.video_mode.bitsPerPixel = 32;
        }

        GameCoordinator game;
        game.run(config);
    }
    catch (const std::exception & ex)
    {
        std::cout << "EXCEPTION ERROR:  \"" << ex.what() << "\"" << std::endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cout << "EXCEPTION ERROR:  \"UNKOWNN\"" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
