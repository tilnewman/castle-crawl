#ifndef CASTLECRAWL_PLAYER_HPP_INCLUDED
#define CASTLECRAWL_PLAYER_HPP_INCLUDED
//
// player.hpp
//
#include <algorithm>
#include <string>

namespace castlecrawl
{

    class Stat
    {
      public:
        Stat(const int value, const int theMin, const int theMax)
            : m_value(value)
            , m_min(theMin)
            , m_max(theMax)
        {}

        int get() const { return m_value; }
        int getMin() const { return m_min; }
        int getMax() const { return m_max; }

        void set(const int newValue)
        {
            m_value = newValue;
            m_value = std::clamp(m_value, m_min, m_max);
        }

        void adj(const int adjustment) { set(m_value + adjustment); }
        void adjMax(const int adjustment) { m_max += adjustment; }

      private:
        int m_value;
        int m_min;
        int m_max;
    };

    //

    class Player
    {
      public:
        Player();

        Stat & strength() { return m_strength; }
        Stat & dexterity() { return m_dexterity; }
        Stat & arcane() { return m_arcane; }
        Stat & health() { return m_health; }

      private:
        constexpr static int statMin = 1;
        constexpr static int statMax = 99;
        constexpr static int statStart = 10;
        constexpr static int healthStart = 20;
        constexpr static int manaStart = 16;

        Stat m_strength;
        Stat m_dexterity;
        Stat m_arcane;
        Stat m_health;
        Stat m_mana;
        Stat m_level;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_PLAYER_HPP_INCLUDED
