#ifndef CASTLECRAWL_PLAYER_HPP_INCLUDED
#define CASTLECRAWL_PLAYER_HPP_INCLUDED
//
// player.hpp
//
#include "item/inventory.hpp"
#include "misc/stat.hpp"

#include <algorithm>
#include <string>

namespace castlecrawl
{

    class Player
    {
      public:
        Player();

        Stat & accuracy() { return m_accuracy; }
        Stat & arcane() { return m_arcane; }
        Stat & dexterity() { return m_dexterity; }
        Stat & luck() { return m_luck; }
        Stat & strength() { return m_strength; }

        Stat & health() { return m_health; }
        Stat & mana() { return m_mana; }

        Stat & level() { return m_level; }

        int gold() const { return m_gold; }
        void adjGold(const int adjustment) { m_gold += adjustment; }

        item::Inventory & inventory() { return m_inventory; }

        void updateEquipEffects();

        friend void to_json(json & j, const Player & p);
        friend void from_json(const json & j, Player & p);

      private:
        constexpr static int statMin = 1;
        constexpr static int statMax = 99;
        constexpr static int statStart = 10;
        constexpr static int healthStart = 20;
        constexpr static int manaStart = 16;

        Stat m_accuracy;
        Stat m_arcane;
        Stat m_dexterity;
        Stat m_luck;
        Stat m_strength;

        Stat m_health;
        Stat m_mana;

        Stat m_level;

        int m_gold;

        item::Inventory m_inventory;

        item::EquipEffect m_equipEffects;
    };

    inline void to_json(json & j, const Player & p)
    {
        // clang-format off
        j = json{ { "accuracy", p.m_accuracy },
                  { "arcane", p.m_arcane },
                  { "dexterity", p.m_dexterity },
                  { "luck", p.m_luck },
                  { "strength", p.m_strength },
                  { "health", p.m_health },
                  { "mana", p.m_mana },
                  { "level", p.m_level },
                  { "gold", p.m_gold },
                  { "inventory", p.m_inventory },
                  { "equip_effects", p.m_equipEffects } };
        // clang-format on
    }

    inline void from_json(const json & j, Player & p)
    {
        j.at("accuracy").get_to(p.m_accuracy);
        j.at("arcane").get_to(p.m_arcane);
        j.at("dexterity").get_to(p.m_dexterity);
        j.at("luck").get_to(p.m_luck);
        j.at("strength").get_to(p.m_strength);
        j.at("health").get_to(p.m_health);
        j.at("mana").get_to(p.m_mana);
        j.at("level").get_to(p.m_level);
        j.at("gold").get_to(p.m_gold);
        j.at("inventory").get_to(p.m_inventory);
        j.at("equip_effects").get_to(p.m_equipEffects);
    }

} // namespace castlecrawl

#endif // CASTLECRAWL_PLAYER_HPP_INCLUDED
