// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// item.cpp
//
#include "item.hpp"

namespace castlecrawl
{
    namespace item
    {
        Item::Item()
            : m_name()
            , m_weapon(Weapon::Not)
            , m_armor(Armor::Not)
            , m_misc(Misc::Not)
            , m_armorRating(0)
            , m_damageMin(0)
            , m_damageMax(0)
            , m_value(0)
        {}

        Item::Item(const std::string & name, const Weapon weapon)
            : m_name(name)
            , m_weapon(weapon)
            , m_armor(Armor::Not)
            , m_misc(Misc::Not)
            , m_armorRating(0)
            , m_damageMin(baseWeaponDamage(weapon).x)
            , m_damageMax(baseWeaponDamage(weapon).y)
            , m_value(calcValue())
        {}

        Item::Item(const std::string & name, const Armor armor)
            : m_name(name)
            , m_weapon(Weapon::Not)
            , m_armor(armor)
            , m_misc(Misc::Not)
            , m_armorRating(baseArmorRating(armor))
            , m_damageMin(0)
            , m_damageMax(0)
            , m_value(calcValue())
        {}

        Item::Item(const std::string & name, const Misc misc)
            : m_name(name)
            , m_weapon(Weapon::Not)
            , m_armor(Armor::Not)
            , m_misc(misc)
            , m_armorRating(0)
            , m_damageMin(0)
            , m_damageMax(0)
            , m_value(calcValue())
        {}

        int Item::calcValue() const
        {
            int value = 0;

            if (isMisc())
            {
                value += 50;
            }

            value += (m_armorRating * 40);
            value += (m_damageMin * 10);
            value += (m_damageMax * 10);

            if (isUseable(m_misc))
            {
                value += 50;
            }

            if (isEquipable(m_misc))
            {
                value += 20;
            }

            return value;
        }

    } // namespace item

} // namespace castlecrawl
