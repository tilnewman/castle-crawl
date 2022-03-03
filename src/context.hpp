#ifndef CASTLECRAWL_CONTEXT_HPP_INCLUDED
#define CASTLECRAWL_CONTEXT_HPP_INCLUDED
//
// context.hpp
//

namespace util
{
    class Random;
    class SoundPlayer;
    class AnimationPlayer;
} // namespace util

namespace castlecrawl
{

    namespace item
    {
        class ItemFactory;
    }

    class Map;
    class Maps;
    class Media;
    class Layout;
    class Player;
    class GameInPlay;
    class StateMachine;
    class PopupManager;

    struct Board;
    struct MapLink;
    struct Process;
    struct GameConfig;
    
    //

    struct Context
    {
        Context(
            GameInPlay & gam,
            Player & pla,
            Maps & mps,
            Board & bor,
            const GameConfig & con,
            Layout & lay,
            Process & pro,
            const Media & med,
            StateMachine & sta,
            PopupManager & pop,
            item::ItemFactory & ifa,
            const util::Random & ran,
            util::SoundPlayer & aud,
            util::AnimationPlayer & ani)
            : game(gam)
            , player(pla)
            , maps(mps)
            , board(bor)
            , config(con)
            , layout(lay)
            , process(pro)
            , media(med)
            , state(sta)
            , popup(pop)
            , items(ifa)
            , random(ran)
            , audio(aud)
            , anim(ani)
        {}

        Context(const Context &) = delete;
        Context(Context &&) = delete;

        Context & operator=(const Context &) = delete;
        Context & operator=(Context &&) = delete;

        GameInPlay & game;
        Player & player;
        Maps & maps;
        Board & board;
        const GameConfig & config;
        Layout & layout;
        Process & process;
        const Media & media;
        StateMachine & state;
        PopupManager & popup;
        item::ItemFactory & items;
        const util::Random & random;
        util::SoundPlayer & audio;
        util::AnimationPlayer & anim;
    };
} // namespace castlecrawl

#endif // CASTLECRAWL_CONTEXT_HPP_INCLUDED
