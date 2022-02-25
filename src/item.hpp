#ifndef CASTLECRAWL_ITEM_HPP_INCLUDED
#define CASTLECRAWL_ITEM_HPP_INCLUDED
//
// maps.hpp
//
#include <string>

namespace castlecrawl
{
    namespace item
    {
        using Flag_t = std::uint8_t;

        enum Flag : Flag_t
        {
            None = 0,
            Wearable = 1 << 0,
            Useable = 1 << 1,
            OneHanded = 1 << 2,
            TwoHanded = 1 << 3,
            Edible = 1 << 4,
        };

        enum class Weapon
        {
            Not = 0,
            Claymore,
            Longsword,
            Sickle,
            Scythe,
            Handaxe,
            Waraxe,
            Mace,
            Warhammer,
            Spear,
            Halberd,
            Staff,
            Dagger
        };

        enum class Armor
        {
            Not,
            Helm,
            Cuirass,
            Gauntlets,
            Greaves,
            Boots
        };

        enum class Misc
        {
            Not,
            Amulet,
            Potion,
            Ring,
            Key
        };

        class Item
        {
          public:
            Item();

            const std::string name() const { return m_name; }
            const std::string description() const { return m_description; }

            bool isWeapon() const { return (m_weapon != Weapon::Not); }
            bool isArmor() const { return (m_armor != Armor::Not); }
            bool isMisc() const { return ((m_misc != Misc::Not)); }

            bool isWearable() const { return (m_flags & Flag::Wearable); }
            bool isUseable() const { return (m_flags & Flag::Useable); }
            bool isOneHanded() const { return (m_flags & Flag::OneHanded); }
            bool isTwoHanded() const { return (m_flags & Flag::TwoHanded); }
            bool isEdible() const { return (m_flags & Flag::Edible); }

          private:
            std::string m_name;
            std::string m_description;
            Weapon m_weapon;
            Armor m_armor;
            Misc m_misc;
            Flag_t m_flags;
            int m_armorClass;
            int m_damageMin;
            int m_damageMax;
        };

    } // namespace item
} // namespace castlecrawl

#endif // CASTLECRAWL_ITEM_HPP_INCLUDED
