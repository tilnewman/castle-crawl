#ifndef CASTLECRAWL_ITEM_HPP_INCLUDED
#define CASTLECRAWL_ITEM_HPP_INCLUDED
//
// item.hpp
//
#include "item-enums.hpp"

#include <iosfwd>
#include <string>
#include <tuple>

namespace castlecrawl
{
    namespace item
    {

        class Item
        {
          public:
            Item(const Weapon weapon, const WeaponMaterial material);
            Item(const Armor armor, const ArmorMaterial material);
            Item(const Misc misc, const MiscMaterial material, const UseStrength strength);

            const std::string name() const;

            Weapon weaponType() const { return m_weapon; }
            Armor armorType() const { return m_armor; }
            Misc miscType() const { return m_misc; }

            int armorRating() const { return m_armorRating; }
            int damageMin() const { return m_damageMin; }
            int damageMax() const { return m_damageMax; }
            int value() const { return m_value; }

            ArmorMaterial armorMaterial() const { return m_armorMaterial; }
            WeaponMaterial weaponMaterial() const { return m_weaponMaterial; }
            MiscMaterial miscMaterial() const { return m_miscMaterial; }

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

            ArmorMaterial m_armorMaterial;
            WeaponMaterial m_weaponMaterial;
            MiscMaterial m_miscMaterial;

            UseStrength m_useStrength;

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
                    left.m_armorMaterial,
                    left.m_weaponMaterial,
                    left.m_miscMaterial,
                    left.m_useStrength,
                    left.m_damageMin,
                    left.m_damageMax,
                    left.m_value) ==
                std::tie(
                    right.m_name,
                    right.m_weapon,
                    right.m_armor,
                    right.m_misc,
                    right.m_armorRating,
                    right.m_armorMaterial,
                    right.m_weaponMaterial,
                    right.m_miscMaterial,
                    right.m_useStrength,
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
                    left.m_armorMaterial,
                    left.m_weaponMaterial,
                    left.m_miscMaterial,
                    left.m_useStrength,
                    left.m_damageMin,
                    left.m_damageMax,
                    left.m_value) <
                std::tie(
                    right.m_name,
                    right.m_weapon,
                    right.m_armor,
                    right.m_misc,
                    right.m_armorRating,
                    right.m_armorMaterial,
                    right.m_weaponMaterial,
                    right.m_miscMaterial,
                    right.m_useStrength,
                    right.m_damageMin,
                    right.m_damageMax,
                    right.m_value));
        }

        std::ostream & operator<<(std::ostream & os, const Item & item);

    } // namespace item
} // namespace castlecrawl

#endif // CASTLECRAWL_ITEM_HPP_INCLUDED
