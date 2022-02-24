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
    class GameInPlay;
    class StateMachine;

    struct Board;
    struct MapLink;
    struct GameConfig;
    struct PopupManager;
    //

    struct Context
    {
        Context(
            GameInPlay & gam,
            Board & bor,
            const GameConfig & con,
            Layout & lay,
            const Media & med,
            StateMachine & sta,
            PopupManager & pop,
            const util::Random & ran)
            : game(gam)
            , board(bor)
            , config(con)
            , layout(lay)
            , media(med)
            , state(sta)
            , popup(pop)
            , random(ran)
            , map_name()
        {}

        Context(const Context &) = delete;
        Context(Context &&) = delete;

        Context & operator=(const Context &) = delete;
        Context & operator=(Context &&) = delete;

        // subsystem references
        GameInPlay & game;
        Board & board;
        const GameConfig & config;
        Layout & layout;
        const Media & media;
        StateMachine & state;
        PopupManager & popup;
        const util::Random & random;

        std::string map_name;
    };
} // namespace mapper

#endif // CASTLECRAWLMAPPER_CONTEXT_HPP_INCLUDED
