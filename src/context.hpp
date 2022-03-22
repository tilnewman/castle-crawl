#ifndef CASTLECRAWL_CONTEXT_HPP_INCLUDED
#define CASTLECRAWL_CONTEXT_HPP_INCLUDED
//
// context.hpp
//

namespace util
{
    class Random;
    class SoundPlayer;
    class MusicPlayer;
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
    class Board;
    class Layout;
    class Player;
    class Summoners;
    class GameInPlay;
    class StateMachine;
    class PopupManager;

    struct MapLink;
    struct Process;
    struct SaveGame;
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
            Media & med,
            Summoners & sum,
            StateMachine & sta,
            PopupManager & pop,
            SaveGame & sav,
            item::ItemFactory & ifa,
            const util::Random & ran,
            util::SoundPlayer & aud,
            util::MusicPlayer & mus,
            util::AnimationPlayer & ani)
            : game(gam)
            , player(pla)
            , maps(mps)
            , board(bor)
            , config(con)
            , layout(lay)
            , process(pro)
            , media(med)
            , summon(sum)
            , state(sta)
            , popup(pop)
            , save(sav)
            , items(ifa)
            , random(ran)
            , audio(aud)
            , music(mus)
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
        Media & media;
        Summoners & summon;
        StateMachine & state;
        PopupManager & popup;
        SaveGame & save;
        item::ItemFactory & items;
        const util::Random & random;
        util::SoundPlayer & audio;
        util::MusicPlayer & music;
        util::AnimationPlayer & anim;
    };
} // namespace castlecrawl

#endif // CASTLECRAWL_CONTEXT_HPP_INCLUDED
