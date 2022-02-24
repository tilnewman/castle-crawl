#ifndef CASTLECRAWLMAPPER_CONTEXT_HPP_INCLUDED
#define CASTLECRAWLMAPPER_CONTEXT_HPP_INCLUDED
//
// context.hpp
//
#include <string>

namespace util
{
    class Random;
} // namespace util

namespace mapper
{
    class Map;
    class Media;
    class Layout;
    class Editor;
    class MapTracker;
    class StateMachine;

    struct Board;
    struct MapLink;
    struct GameConfig;
    struct PopupManager;
    //

    struct Context
    {
        Context(
            Board & bor,
            MapTracker & mtr,
            Editor & edi,
            const GameConfig & con,
            Layout & lay,
            const Media & med,
            StateMachine & sta,
            PopupManager & pop,
            const util::Random & ran)
            : board(bor)
            , map(mtr)
            , editor(edi)
            , config(con)
            , layout(lay)
            , media(med)
            , state(sta)
            , popup(pop)
            , random(ran)
        {}

        Context(const Context &) = delete;
        Context(Context &&) = delete;

        Context & operator=(const Context &) = delete;
        Context & operator=(Context &&) = delete;

        // subsystem references
        Board & board;
        MapTracker & map;
        Editor & editor;
        const GameConfig & config;
        Layout & layout;
        const Media & media;
        StateMachine & state;
        PopupManager & popup;
        const util::Random & random;
    };
} // namespace mapper

#endif // CASTLECRAWLMAPPER_CONTEXT_HPP_INCLUDED
