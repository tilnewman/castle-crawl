#ifndef CASTLECRAWL_PLAYER_HPP_INCLUDED
#define CASTLECRAWL_PLAYER_HPP_INCLUDED
//
// player.hpp
//
#include <algorithm>
#include <string>

namespace castlecrawl
{
    // Tracks a player's stat (i.e. strength) which is the m_normal value that
    // is always clamped between a min and max, but can be temporarily changed
    // by magical items etc so this also tracks a m_current value that can
    // fluctuate higher or lower.
    class Stat
    {
      public:
        Stat(const int value, const int theMin, const int theMax)
            : m_current(value)
            , m_normal(value)
            , m_min(theMin)
            , m_max(theMax)
        {}

        int current() const { return m_current; }
        int normal() const { return m_normal; }

        int min() const { return m_min; }
        int max() const { return m_max; }

        void adjCurrent(const int adjustment) { current(m_current + adjustment); }
        void adjNormal(const int adjustment) { normal(m_normal + adjustment); }
         
        void current(const int newValue)
        {
            m_current = newValue;
            m_current = std::clamp(m_current, m_min, m_max);
        }

        void normal(const int newValue)
        {
            m_normal = newValue;
            m_normal = std::clamp(m_normal, m_min, m_max);
        }

        void reset() { m_current = m_normal; }

      private:
        int m_current;
        int m_normal;
        int m_min;
        int m_max;
    };

    //

    class Player
    {
      public:
        Player();

        Stat & arcane() { return m_arcane; }
        Stat & dexterity() { return m_dexterity; }
        Stat & luck() { return m_luck; }
        Stat & strength() { return m_strength; }
        
        Stat & health() { return m_health; }
        Stat & mana() { return m_mana; }

        Stat & level() { return m_level; }

        int gold() const { return m_gold; }
        void adjGold(const int adjustment) { m_gold += adjustment; }

      private:
        constexpr static int statMin = 1;
        constexpr static int statMax = 99;
        constexpr static int statStart = 10;
        constexpr static int healthStart = 20;
        constexpr static int manaStart = 16;

        Stat m_arcane;
        Stat m_dexterity;
        Stat m_luck;
        Stat m_strength;
        
        Stat m_health;
        Stat m_mana;
        
        Stat m_level;
        
        int m_gold;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_PLAYER_HPP_INCLUDED
