#ifndef CASTLECRAWL_ENEMY_HPP_INCLUDED
#define CASTLECRAWL_ENEMY_HPP_INCLUDED
//
// enemy.hpp
//
#include "map-types.hpp"
#include "summon-image.hpp"

#include <vector>

namespace util
{
    class Random;
}

namespace castlecrawl
{

    struct Context;

    enum class Enemy
    {
        Snake,
        Spider,
        Goblin,
        Bat,
        Pixie,
        Skeleton,
        Demon,
        Dragon,
        Wizard
    };

    inline SummonImage randomSummonImage(const util::Random & random, const Enemy enemy) noexcept
    {
        // clang-format off
        switch (enemy)
        {
            case Enemy::Snake:    { return randomSummonImage(random, SummonImage::Snake1); }
            case Enemy::Spider:   { return randomSummonImage(random, SummonImage::Spider1); }
            case Enemy::Goblin:   { return randomSummonImage(random, SummonImage::Goblin1); }
            case Enemy::Bat:      { return randomSummonImage(random, SummonImage::Bat1); }
            case Enemy::Pixie:    { return randomSummonImage(random, SummonImage::Pixie1); }
            case Enemy::Skeleton: { return randomSummonImage(random, SummonImage::Skeleton1); }
            case Enemy::Demon:    { return randomSummonImage(random, SummonImage::Demon1); }
            case Enemy::Dragon:   { return randomSummonImage(random, SummonImage::Dragon1); }
            case Enemy::Wizard:   
            default:              { return randomSummonImage(random, SummonImage::Wizard1); }
        }
        // clang-format on
    }

    inline float turnTimeSec(const Enemy enemy) noexcept
    {
        // clang-format off
        switch (enemy)
        {
            case Enemy::Snake:      { return 2.0f; }
            case Enemy::Spider:     { return 2.5f; }
            case Enemy::Goblin:     { return 3.5f; }
            case Enemy::Bat:        { return 1.5f; }
            case Enemy::Pixie:      { return 3.0f; }
            case Enemy::Skeleton:   { return 4.0f; }
            case Enemy::Demon:      { return 4.5f; }
            case Enemy::Dragon:     { return 5.0f; }
            case Enemy::Wizard:
            default:                { return 3.0f; }
        }
        // clang-format on
    }

    struct EnemyInstance
    {
        Enemy enemy{ Enemy::Snake }; // any works here
        MapPos_t position{ 0, 0 };
        float timer_sec{ 0.0f };
    };

    //

    class Enemies
    {
      public:
        Enemies();

        void update(Context & context, const float frameTimeSec);
        void add(const EnemyInstance & ei);
        void remove(const MapPos_t & position);

      private:
        void act(Context & context);

      private:
        std::vector<EnemyInstance> m_enemies;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_ENEMY_HPP_INCLUDED
