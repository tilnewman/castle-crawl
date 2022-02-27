#ifndef CASTLECRAWL_ITEM_HPP_INCLUDED
#define CASTLECRAWL_ITEM_HPP_INCLUDED
//
// item.hpp
//
#include <iosfwd>
#include <string>
#include <tuple>

#include <SFML/System/Vector2.hpp>

namespace castlecrawl
{
    namespace item
    {

        enum class Weapon
        {
            Dagger = 0,
            Handaxe,
            Mace,
            Warhammer,
            Shortsword,
            Longsword,
            Claymore,
            Waraxe,
            Scythe,
            Count
        };

        inline const std::string weaponName(const Weapon weapon)
        {
            // clang-format off
            switch (weapon)
            {
                case Weapon::Dagger:        { return "Dagger"; }
                case Weapon::Handaxe:       { return "Handaxe"; }
                case Weapon::Mace:          { return "Mace"; }
                case Weapon::Warhammer:     { return "Warhammer"; }
                case Weapon::Shortsword:    { return "Shortsword"; }
                case Weapon::Longsword:     { return "Longsword"; }
                case Weapon::Claymore:      { return "Claymore"; }
                case Weapon::Waraxe:        { return "Waraxe"; }
                case Weapon::Scythe:        { return "Scythe"; }
                case Weapon::Count:
                default:                    { return ""; }
            }
            // clang-format on
        }

        enum class Armor
        {
            Helm = 0,
            Cuirass,
            Bracers,
            Gauntlets,
            Greaves,
            Boots,
            Count
        };

        inline const std::string armorName(const Armor armor)
        {
            // clang-format off
            switch (armor)
            {
                case Armor::Helm:       { return "Helm"; }
                case Armor::Cuirass:    { return "Cuirass"; }
                case Armor::Bracers:    { return "Bracers"; }
                case Armor::Gauntlets:  { return "Gauntlets"; }
                case Armor::Greaves:    { return "Greaves"; }
                case Armor::Boots:      { return "Boots"; }
                case Armor::Count:
                default:                { return ""; }
            }
        }
        // clang-format on

        enum class Misc
        {
            Amulet = 0,
            Potion,
            Ring,
            Charm,
            Feather,
            Mask,
            Talisman,
            Herbs,
            Count
        };

        inline const std::string miscName(const Misc misc)
        {
            // clang-format off
            switch (misc)
            {
                case Misc::Amulet:      { return "Amulet"; }
                case Misc::Potion:      { return "Potion"; }
                case Misc::Ring:        { return "Ring"; }
                case Misc::Charm:       { return "Charm"; }
                case Misc::Feather:     { return "Feather"; }
                case Misc::Mask:        { return "Mask"; }
                case Misc::Talisman:    { return "Talisman"; }
                case Misc::Herbs:       { return "Herbs"; }
                case Misc::Count:
                default:                { return ""; }
            }
            // clang-format on
        }

        inline const sf::Vector2i baseWeaponDamage(const Weapon weapon)
        {
            // clang-format off
            switch (weapon)
            {
                case Weapon::Dagger:     { return {  2,  4 }; }
                case Weapon::Handaxe:    { return {  3,  6 }; }
                case Weapon::Mace:       { return {  9, 13 }; }
                case Weapon::Warhammer:  { return { 10, 16 }; }
                case Weapon::Shortsword: { return {  6, 10 }; }
                case Weapon::Longsword:  { return {  9, 13 }; }
                case Weapon::Claymore:   { return { 10, 16 }; }
                case Weapon::Waraxe:     { return { 12, 18 }; }
                case Weapon::Scythe:     { return { 13, 20 }; }
                case Weapon::Count:
                default:                 { return {  0,  0 }; }
            }
            // clang-format on
        }

        inline int baseArmorRating(const Armor armor)
        {
            // clang-format off
            switch (armor)
            {
                case Armor::Helm:       { return 5; }
                case Armor::Cuirass:    { return 9; }
                case Armor::Bracers:    { return 3; }
                case Armor::Gauntlets:  { return 2; }
                case Armor::Greaves:    { return 6; }
                case Armor::Boots:      { return 1; }
                case Armor::Count:
                default:                { return 0; }
            }
            // clang-format on
        }

        inline bool isMiscUseable(const Misc misc)
        {
            // clang-format off
            switch (misc)
            {
                case Misc::Amulet:    { return false; }
                case Misc::Potion:    { return true;  }
                case Misc::Ring:      { return false; }
                case Misc::Charm:     { return false; }
                case Misc::Feather:   { return false; }
                case Misc::Mask:      { return false; }
                case Misc::Talisman:  { return false; }
                case Misc::Herbs:     { return true;  }
                case Misc::Count:
                default:              { return false; }
            }
            // clang-format on
        }

        // if not misc, then it's either weapon/armor which can only equip one of
        inline std::size_t miscEquipCount(const Misc misc)
        {
            // clang-format off
            switch (misc)
            {
                case Misc::Amulet:    { return 1; }
                case Misc::Potion:    { return 0; }
                case Misc::Ring:      { return 2; }
                case Misc::Charm:     { return 1; }
                case Misc::Feather:   { return 0; }
                case Misc::Mask:      { return 1; }
                case Misc::Talisman:  { return 0; }
                case Misc::Herbs:     { return 0; }
                case Misc::Count:
                default:              { return 1; }
            }
            // clang-format on
        }

        inline bool isMiscEquipable(const Misc misc) { return (miscEquipCount(misc) > 0); }

        //

        class Item
        {
          public:
            // leaves the item in what should be the one and only invalid state
            Item();

            Item(const std::string & name, const Weapon weapon);
            Item(const std::string & name, const Armor armor);
            Item(const std::string & name, const Misc misc);

            const std::string name() const { return m_name; }

            Weapon weaponType() const { return m_weapon; }
            Armor armorType() const { return m_armor; }
            Misc miscType() const { return m_misc; }

            int armorRating() const { return m_armorRating; }
            int damageMin() const { return m_damageMin; }
            int damageMax() const { return m_damageMax; }
            int value() const { return m_value; }

            // these three are mutually exclusive but one must be true to be valid
            bool isWeapon() const { return (m_weapon != Weapon::Count); }
            bool isArmor() const { return (m_armor != Armor::Count); }
            bool isMisc() const { return ((m_misc != Misc::Count)); }

            bool isUseable() const { return isMiscUseable(m_misc); }
            std::size_t equipCount() const { return miscEquipCount(m_misc); }
            bool isEquipable() const { return isMiscEquipable(m_misc); }

            const std::string description() const;

            friend bool operator==(const Item & left, const Item & right);
            friend bool operator!=(const Item & left, const Item & right);
            friend bool operator<(const Item & left, const Item & right);
            friend std::ostream & operator<<(std::ostream & os, const Item & item);

          private:
            int calcValue() const;

          private:
            std::string m_name;

            Weapon m_weapon;
            Armor m_armor;
            Misc m_misc;

            int m_armorRating;
            int m_damageMin;
            int m_damageMax;
            int m_value;
        };

        inline bool operator==(const Item & left, const Item & right)
        {
            return (
                std::tie(
                    left.m_name,
                    left.m_weapon,
                    left.m_armor,
                    left.m_misc,
                    left.m_armorRating,
                    left.m_damageMin,
                    left.m_damageMax,
                    left.m_value) ==
                std::tie(
                    right.m_name,
                    right.m_weapon,
                    right.m_armor,
                    right.m_misc,
                    right.m_armorRating,
                    right.m_damageMin,
                    right.m_damageMax,
                    right.m_value));
        }

        inline bool operator!=(const Item & left, const Item & right) { return !(left == right); }

        inline bool operator<(const Item & left, const Item & right)
        {
            return (
                std::tie(
                    left.m_name,
                    left.m_weapon,
                    left.m_armor,
                    left.m_misc,
                    left.m_armorRating,
                    left.m_damageMin,
                    left.m_damageMax,
                    left.m_value) <
                std::tie(
                    right.m_name,
                    right.m_weapon,
                    right.m_armor,
                    right.m_misc,
                    right.m_armorRating,
                    right.m_damageMin,
                    right.m_damageMax,
                    right.m_value));
        }

        std::ostream & operator<<(std::ostream & os, const Item & item);

    } // namespace item
} // namespace castlecrawl

#endif // CASTLECRAWL_ITEM_HPP_INCLUDED
