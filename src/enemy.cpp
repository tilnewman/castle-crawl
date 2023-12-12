// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// enemy.cpp
//
#include "enemy.hpp"

#include "context.hpp"
#include "sfml-util.hpp"

namespace castlecrawl
{

    Enemies::Enemies()
        : m_enemies()
    {}

    void Enemies::update(Context & context, const float frameTimeSec)
    {
        for (EnemyInstance & instance : m_enemies)
        {
            instance.timer_sec -= frameTimeSec;
            if (instance.timer_sec < 0.0f)
            {
                instance.timer_sec = turnTimeSec(instance.enemy);
                act(context);
            }
        }
    }

    void Enemies::add(const EnemyInstance & ei) { m_enemies.push_back(ei); }

    void Enemies::remove(const MapPos_t & pos)
    {
        m_enemies.erase(
            std::remove_if(
                std::begin(m_enemies),
                std::end(m_enemies),
                [&](const EnemyInstance & si) { return (si.position == pos); }),
            std::end(m_enemies));
    }

    void Enemies::act(Context &) {}

} // namespace castlecrawl
