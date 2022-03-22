#ifndef CASTLECRAWL_SUMMONER_HPP_INCLUDED
#define CASTLECRAWL_SUMMONER_HPP_INCLUDED
//
// summoner.hpp
//
#include "enemy.hpp"
#include "map-types.hpp"
#include "pieces.hpp"
#include "summon-image.hpp"

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
        PixieGoblet,
        SkeletonGrave,
        DemonDoor,
        DragonBreath,
        WizardTomb
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
            case Summoner::PixieGoblet:   { return Pieces::PixieGoblet; }
            case Summoner::SkeletonGrave: { return Pieces::SkeletonGrave; }
            case Summoner::DemonDoor:     { return Pieces::DemonDoor; }
            case Summoner::DragonBreath:  { return Pieces::DragonBreath; }
            case Summoner::WizardTomb:    
            default:                      { return Pieces::WizardTomb; }
        }
        // clang-format on
    }

    inline constexpr SummonImage summonImage(const Summoner summoner) noexcept
    {
        // clang-format off
        switch (summoner)
        {
            case Summoner::SnakeBag:      { return SummonImage::SnakeBag; }
            case Summoner::SpiderWeb:     { return SummonImage::SpiderWeb; }
            case Summoner::GoblinPot:     { return SummonImage::GoblinPot; }
            case Summoner::BirdMask:      { return SummonImage::BirdMask; }
            case Summoner::PixieGoblet:   { return SummonImage::PixieGoblet; }
            case Summoner::SkeletonGrave: { return SummonImage::SkeletonGrave; }
            case Summoner::DemonDoor:     { return SummonImage::DemonDoor; }
            case Summoner::DragonBreath:  { return SummonImage::DragonBreath; }
            case Summoner::WizardTomb:    
            default:                      { return SummonImage::WizardTomb; }
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
            case Summoner::PixieGoblet:   { return 15.0f; }
            case Summoner::SkeletonGrave: { return 17.0f; }
            case Summoner::DemonDoor:     { return 30.0f; }
            case Summoner::DragonBreath:  { return 20.0f; }
            case Summoner::WizardTomb:
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
        void remove(const MapPos_t & position);

      private:
        void summon(Context & context);

      private:
        std::vector<SummonerInstance> m_summoners;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_SUMMONER_HPP_INCLUDED
