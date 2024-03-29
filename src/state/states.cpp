// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// states.cpp
//
#include "state/states.hpp"

#include "audio/music-player.hpp"
#include "audio/sound-player.hpp"
#include "display/animation-player.hpp"
#include "display/layout.hpp"
#include "display/media.hpp"
#include "item/inventory.hpp"
#include "item/item-factory.hpp"
#include "map/maps.hpp"
#include "map/summoner.hpp"
#include "misc/context.hpp"
#include "misc/game.hpp"
#include "misc/player.hpp"
#include "state/state-machine.hpp"

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

        context.game.setup();

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

        // TODO TEMP remove after testing
        SummonerInstance si;
        si.position = { 7, 2 };
        si.summoner = Summoner::SpiderWeb;
        si.timer_sec = 10.0f;
        context.summon.add(context, si);
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
