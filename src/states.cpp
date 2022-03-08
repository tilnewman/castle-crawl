// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// states.cpp
//
#include "states.hpp"

#include "animation-player.hpp"
#include "context.hpp"
#include "item-factory.hpp"
#include "maps.hpp"
#include "media.hpp"
#include "music-player.hpp"
#include "settings.hpp"
#include "sound-player.hpp"
#include "state-machine.hpp"

#include <ostream>

namespace castlecrawl
{

    StateBase::StateBase(const State state)
        : m_state(state)
    {}

    void StateLoad::onEnter(Context & context)
    {
        // Note this order is critical to making Context ready to use

        sf::Clock clock;

        context.game.reset();

        context.items.processAll();
        // context.items.printSummaries();

        context.layout.calcWindowValues(context.config);

        context.audio.setMediaPath((context.config.media_dir_path / "sfx").string());
        context.audio.volume(75.0f);

        context.music.setup(context.config.media_dir_path / "music");
        context.music.start("music.ogg", 18.0f);

        context.anim.setMediaPath((context.config.media_dir_path / "anim").string());

        context.media.load(context.config, context.layout, context.audio);

        context.maps.loadAll(context.random);

        context.maps.switchTo(context, { { 0, 0 }, "level-1-first-room", { 5, 3 } });

        const int loadTimeMs = clock.getElapsedTime().asMilliseconds();
        std::cout << "Load time: " << loadTimeMs << "ms" << std::endl;

        context.state.setChangePending(State::Splash);
    }

    void StateQuit::onEnter(Context & context)
    {
        context.music.stopAll();
        context.game.endGame(false);
    }

    std::ostream & operator<<(std::ostream & os, const State state)
    {
        os << toString(state);
        return os;
    }

} // namespace castlecrawl
