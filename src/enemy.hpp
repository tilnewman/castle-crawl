#ifndef CASTLECRAWL_ENEMY_HPP_INCLUDED
#define CASTLECRAWL_ENEMY_HPP_INCLUDED
//
// enemy.hpp
//
#include "map-types.hpp"
#include "tile-image.hpp"

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

    inline TileImage tileImage(const Enemy enemy) noexcept
    {
        // clang-format off
        switch (enemy)
        {
            case Enemy::Snake:    { return TileImage::Snake; }
            case Enemy::Spider:   { return TileImage::Spider; }
            case Enemy::Goblin:   { return TileImage::Goblin; }
            case Enemy::Bat:      { return TileImage::Bat; }
            case Enemy::Skeleton: { return TileImage::Skeleton; }
            case Enemy::Demon:    { return TileImage::Demon; }
            case Enemy::Dragon:   { return TileImage::Dragon; }
            default:              { return TileImage::Empty; }
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
