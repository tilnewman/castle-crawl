#ifndef CASTLECRAWL_ITEM_HPP_INCLUDED
#define CASTLECRAWL_ITEM_HPP_INCLUDED
//
// item.hpp
//
#include "item-enums.hpp"

#include <iosfwd>
#include <string>
#include <tuple>
#include <compare>

namespace castlecrawl
{
    namespace item
    {

        class Item
        {
          public:
            // the default constructor makes an invalid item
            Item();

            // normal weapon constructor  
            Item(const Weapon weapon, const WeaponMaterial material);

            // magical weapon constructor
            Item(
                const Weapon weapon,
                const WeaponMaterial material,
                const std::string & uniqueName,
                const EquipEffect & effect);

            // normal armor constructor
            Item(const Armor armor, const ArmorMaterial material);

            // magical armor constructor
            Item(
                const Armor armor,
                const ArmorMaterial material,
                const std::string & uniqueName,
                const EquipEffect & effect);

            // misc item constructor (all misc items are magical)
            Item(
                const Misc misc,
                const MiscMaterial material,
                const UseStrength strength,
                const UseEffect & useEffect,
                const EquipEffect & equipEffect);

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

            const UseEffect & useEffect() const { return m_useEffect; }
            const EquipEffect & equipEffect() const { return m_equipEffect; }

            bool isMagical() const { return (!m_useEffect.empty() || !m_equipEffect.empty()); }
            
            const std::string description() const;

            auto operator<=>(const Item &) const = default;
            friend std::ostream & operator<<(std::ostream & os, const Item & item);

          private:
            int calcValue() const;

          private:
            // keeping value first ensures sorting by value first
            int m_value;

            Weapon m_weapon;
            Armor m_armor;
            Misc m_misc;

            std::string m_name;

            ArmorMaterial m_armorMaterial;
            WeaponMaterial m_weaponMaterial;
            MiscMaterial m_miscMaterial;

            UseStrength m_useStrength;

            int m_armorRating;
            int m_damageMin;
            int m_damageMax;
            
            UseEffect m_useEffect;
            EquipEffect m_equipEffect;
        };

        std::ostream & operator<<(std::ostream & os, const Item & item);

    } // namespace item
} // namespace castlecrawl

#endif // CASTLECRAWL_ITEM_HPP_INCLUDED
