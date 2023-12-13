#ifndef CASTLECRAWL_SUMMONER_HPP_INCLUDED
#define CASTLECRAWL_SUMMONER_HPP_INCLUDED
//
// summoner.hpp
//
#include "display/tile-image.hpp"
#include "map/enemy.hpp"
#include "map/map-types.hpp"
#include "map/pieces.hpp"

#include <vector>

namespace castlecrawl
{

    struct Context;

    enum class Summoner
    {
        SnakeBag,
        SpiderWeb,
        GoblinPot,
        BirdMask,
        SkeletonGrave,
        DemonDoor,
        DragonBreath
    };

    inline constexpr Pieces piece(const Summoner summoner) noexcept
    {
        // clang-format off
        switch (summoner)
        {
            case Summoner::SnakeBag:      { return Pieces::SnakeBag; }
            case Summoner::SpiderWeb:     { return Pieces::SpiderWeb; }
            case Summoner::GoblinPot:     { return Pieces::GoblinPot; }
            case Summoner::BirdMask:      { return Pieces::BirdMask; }
            case Summoner::SkeletonGrave: { return Pieces::SkeletonGrave; }
            case Summoner::DemonDoor:     { return Pieces::DemonDoor; }
            case Summoner::DragonBreath:
            default:                      { return Pieces::DragonBreath; }
        }
        // clang-format on
    }

    inline constexpr TileImage tileImage(const Summoner summoner) noexcept
    {
        // clang-format off
        switch (summoner)
        {
            case Summoner::SnakeBag:      { return TileImage::SnakeBag; }
            case Summoner::SpiderWeb:     { return TileImage::SpiderWeb; }
            case Summoner::GoblinPot:     { return TileImage::GoblinPot; }
            case Summoner::BirdMask:      { return TileImage::BirdMask; }
            case Summoner::SkeletonGrave: { return TileImage::SkeletonGrave; }
            case Summoner::DemonDoor:     { return TileImage::DemonDoor; }
            case Summoner::DragonBreath:  { return TileImage::DragonBreath; }
            default:                      { return TileImage::Empty; }
        }
        // clang-format on
    }

    inline float summonRateSec(const Summoner summoner) noexcept
    {
        // clang-format off
        switch (summoner)
        {
            case Summoner::SnakeBag:      { return 10.0f; }
            case Summoner::SpiderWeb:     { return 10.0f; }
            case Summoner::GoblinPot:     { return 14.0f; }
            case Summoner::BirdMask:      { return 10.0f; }
            case Summoner::SkeletonGrave: { return 17.0f; }
            case Summoner::DemonDoor:     { return 30.0f; }
            case Summoner::DragonBreath:
            default:                      { return 20.0f; }
        }
        // clang-format on
    }

    struct SummonerInstance
    {
        Summoner summoner{ Summoner::SnakeBag }; // any works here
        MapPos_t position{ 0, 0 };
        float timer_sec{ 0.0f };
    };

    //

    class Summoners
    {
      public:
        Summoners();

        void update(Context & context, const float frmaeTimeSec);
        void add(Context & context, const SummonerInstance & si);
        void remove(Context & context, const MapPos_t & position);

      private:
        void summon(Context & context);

      private:
        std::vector<SummonerInstance> m_summoners;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_SUMMONER_HPP_INCLUDED
