// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// item.cpp
//
#include "item.hpp"

#include <ostream>
#include <sstream>

namespace castlecrawl
{
    namespace item
    {
        Item::Item()
            : m_name()
            , m_weapon(Weapon::Count)
            , m_armor(Armor::Count)
            , m_misc(Misc::Count)
            , m_armorRating(0)
            , m_damageMin(0)
            , m_damageMax(0)
            , m_value(0)
        {}

        Item::Item(const std::string & name, const Weapon weapon)
            : m_name(name)
            , m_weapon(weapon)
            , m_armor(Armor::Count)
            , m_misc(Misc::Count)
            , m_armorRating(0)
            , m_damageMin(baseWeaponDamage(weapon).x)
            , m_damageMax(baseWeaponDamage(weapon).y)
            , m_value(calcValue())
        {}

        Item::Item(const std::string & name, const Armor armor)
            : m_name(name)
            , m_weapon(Weapon::Count)
            , m_armor(armor)
            , m_misc(Misc::Count)
            , m_armorRating(baseArmorRating(armor))
            , m_damageMin(0)
            , m_damageMax(0)
            , m_value(calcValue())
        {}

        Item::Item(const std::string & name, const Misc misc)
            : m_name(name)
            , m_weapon(Weapon::Count)
            , m_armor(Armor::Count)
            , m_misc(misc)
            , m_armorRating(0)
            , m_damageMin(0)
            , m_damageMax(0)
            , m_value(calcValue())
        {}

        const std::string Item::description() const
        {
            std::string str;
            str.reserve(200);

            str += "The ";
            str += m_name;
            str += " is ";

            if (isWeapon())
            {
                str += "a ";

                if (m_name != weaponName(m_weapon))
                {
                    str += weaponName(m_weapon);
                    str += ' ';
                }

                str += "weapon that does between ";
                str += std::to_string(m_damageMin);
                str += " and ";
                str += std::to_string(m_damageMax);
                str += " damage";
            }
            else if (isArmor())
            {
                if (m_name != armorName(m_armor))
                {
                    str += armorName(m_armor);
                    str += ' ';
                }

                str += "armor that has a rating of ";
                str += std::to_string(m_armorRating);
            }
            else
            {
                // must be a misc item
                str += "a misc item";

                if (isUseable())
                {
                    str += " that is useable";
                }

                const auto eqCount = equipCount();
                if (eqCount > 0)
                {
                    str += " that you can equip";

                    if (eqCount > 1)
                    {
                        str += ' ';
                        str += std::to_string(eqCount);
                        str += " of";
                    }
                }
            }

            str += '.';
            return str;
        }

        int Item::calcValue() const
        {
            int value = 100;

            value += (m_armorRating * 33);
            value += (m_damageMin * 10);
            value += (m_damageMax * 10);

            if (isUseable())
            {
                value += 50;
            }

            if (isEquipable())
            {
                value += 20;
            }

            return value;
        }

        std::ostream & operator<<(std::ostream & os, const Item & item)
        {
            os << '[';

            if (item.isArmor())
            {
                os << "Armor=" << armorName(item.armorType());
            }

            if (item.isWeapon())
            {
                os << "Weapon=" << weaponName(item.weaponType());
            }

            if (item.isMisc())
            {
                os << "Misc=" << miscName(item.miscType());
            }

            os << ",\"" << item.name() << '\"';

            if (item.armorRating() != 0)
            {
                os << ",armorRating=" << item.armorRating();
            }

            if ((item.damageMin() != 0) || (item.damageMax() != 0))
            {
                os << ",damage=" << item.damageMin() << '-' << item.damageMax();
            }
            if (item.isUseable())
            {
                os << ",useable";
            }

            if (item.equipCount() > 1)
            {
                os << ",equip_count=" << item.equipCount();
            }
            else if (item.equipCount() == 1)
            {
                os << ",equipable";
            }

            os << ",value=" << item.value();

            os << ']';
            return os;
        }

    } // namespace item

} // namespace castlecrawl
