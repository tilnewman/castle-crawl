#ifndef CASTLECRAWL_ITEM_HPP_INCLUDED
#define CASTLECRAWL_ITEM_HPP_INCLUDED
//
// item.hpp
//
#include "item-enums.hpp"

#include <compare>
#include <ostream>
#include <string>
#include <tuple>
#include <vector>

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
            friend void to_json(json & j, const Item & i);
            friend void from_json(const json & j, Item & i);

          private:
            int calcValue() const;

          private:
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

        using ItemVec_t = std::vector<Item>;

        std::ostream & operator<<(std::ostream & os, const Item & item);

        inline void to_json(json & j, const Item & i)
        {
            j = json{ { "value", i.m_value },
                      { "weapon", i.m_weapon },
                      { "armor", i.m_armor },
                      { "misc", i.m_misc },
                      { "name", i.m_name },
                      { "armor_material", i.m_armorMaterial },
                      { "weapon_material", i.m_weaponMaterial },
                      { "misc_material", i.m_miscMaterial },
                      { "use_strength", i.m_useStrength },
                      { "armor_rating", i.m_armorRating },
                      { "damage_min", i.m_damageMin },
                      { "damage_max", i.m_damageMax },
                      { "use_effect", i.m_useEffect },
                      { "equip_effect", i.m_equipEffect } };
        }

        inline void from_json(const json & j, Item & i)
        {
            j.at("value").get_to(i.m_value);
            j.at("weapon").get_to(i.m_weapon);
            j.at("armor").get_to(i.m_armor);
            j.at("misc").get_to(i.m_misc);
            j.at("name").get_to(i.m_name);
            j.at("armor_material").get_to(i.m_armorMaterial);
            j.at("weapon_material").get_to(i.m_weaponMaterial);
            j.at("misc_material").get_to(i.m_miscMaterial);
            j.at("use_strength").get_to(i.m_useStrength);
            j.at("armor_rating").get_to(i.m_armorRating);
            j.at("damage_min").get_to(i.m_damageMin);
            j.at("damage_max").get_to(i.m_damageMax);
            j.at("use_effect").get_to(i.m_useEffect);
            j.at("equip_effect").get_to(i.m_equipEffect);
        }

    } // namespace item
} // namespace castlecrawl

#endif // CASTLECRAWL_ITEM_HPP_INCLUDED
