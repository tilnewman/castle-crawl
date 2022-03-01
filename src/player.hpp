#ifndef CASTLECRAWL_PLAYER_HPP_INCLUDED
#define CASTLECRAWL_PLAYER_HPP_INCLUDED
//
// player.hpp
//
#include "inventory.hpp"

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

        friend void to_json(json & j, const Stat & s);
        friend void from_json(const json & j, Stat & s);

      private:
        int m_current;
        int m_normal;
        int m_min;
        int m_max;
    };

    
    inline void to_json(json & j, const Stat & s)
    {
        j = json{ 
            { "current", s.m_current }, 
            { "normal", s.m_normal },
            { "min", s.m_min },
            { "max", s.m_max }
        };
    }

    inline void from_json(const json & j, Stat & s)
    {
        j.at("current").get_to(s.m_current);
        j.at("normal").get_to(s.m_normal);
        j.at("min").get_to(s.m_min);
        j.at("max").get_to(s.m_max);
    }

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

        friend void to_json(json & j, const Player & p);
        friend void from_json(const json & j, Player & p);

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

    inline void to_json(json & j, const Player & p)
    {
        j = json{ { "arcane", p.m_arcane },
                  { "dexterity", p.m_dexterity },
                  { "luck", p.m_luck },
                  { "strength", p.m_strength },
                  { "health", p.m_health }, 
                  { "mana", p.m_mana },
                  { "level", p.m_level },
                  { "gold", p.m_gold }
        };
    }

    inline void from_json(const json & j, Player & p)
    {
        j.at("arcane").get_to(p.m_arcane);
        j.at("dexterity").get_to(p.m_dexterity);
        j.at("luck").get_to(p.m_luck);
        j.at("strength").get_to(p.m_strength);
        j.at("health").get_to(p.m_health); 
        j.at("mana").get_to(p.m_mana);
        j.at("level").get_to(p.m_level);
        j.at("gold").get_to(p.m_gold);
    }

} // namespace castlecrawl

#endif // CASTLECRAWL_PLAYER_HPP_INCLUDED
