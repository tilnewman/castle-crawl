// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// item.cpp
//
#include "item.hpp"

#include <ostream>

namespace castlecrawl
{
    namespace item
    {
        Item::Item(const Weapon weapon, const WeaponMaterial material)
            : m_name(weaponName(weapon))
            , m_weapon(weapon)
            , m_armor(Armor::Count)
            , m_misc(Misc::Count)
            , m_armorMaterial(ArmorMaterial::Count)
            , m_weaponMaterial(material)
            , m_armorRating(0)
            , m_damageMin(baseWeaponDamage(weapon).x + weaponMaterialDamage(material))
            , m_damageMax(baseWeaponDamage(weapon).y + weaponMaterialDamage(material))
            , m_value(calcValue())
        {}

        Item::Item(const Armor armor, const ArmorMaterial material)
            : m_name(armorName(armor))
            , m_weapon(Weapon::Count)
            , m_armor(armor)
            , m_misc(Misc::Count)
            , m_armorMaterial(material)
            , m_weaponMaterial(WeaponMaterial::Count)
            , m_armorRating(baseArmorRating(armor) + armorMaterialRating(material))
            , m_damageMin(0)
            , m_damageMax(0)
            , m_value(calcValue())
        {}

        Item::Item(const Misc misc)
            : m_name(miscName(misc))
            , m_weapon(Weapon::Count)
            , m_armor(Armor::Count)
            , m_misc(misc)
            , m_armorMaterial(ArmorMaterial::Count)
            , m_weaponMaterial(WeaponMaterial::Count)
            , m_armorRating(0)
            , m_damageMin(0)
            , m_damageMax(0)
            , m_value(calcValue())
        {}

        const std::string Item::name() const
        {
            if (isArmor())
            {
                return armorMaterialName(m_armorMaterial) + " " + m_name;
            }
            else if (isWeapon())
            {
                return weaponMaterialName(m_weaponMaterial) + " " + m_name;
            }
            else
            {
                return m_name;
            }
        }

        const std::string Item::description() const
        {
            std::string str;
            str.reserve(200);

            str += name();
            str += " is";

            if (isWeapon())
            {
                str += " a weapon that does between ";
                str += std::to_string(m_damageMin);
                str += " and ";
                str += std::to_string(m_damageMax);
                str += " damage";
            }
            else if (isArmor())
            {
                str += " armor that has a rating of ";
                str += std::to_string(m_armorRating);
            }
            else // must be a misc item
            {
                str += " a misc item";

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
            os << "\"" << item.name() << '\"';

            if (item.isArmor())
            {
                os << "(Armor)";
            }

            if (item.isWeapon())
            {
                os << "(Weapon)";
            }

            if (item.isMisc())
            {
                os << "(Misc)";
            }

            if (item.armorRating() != 0)
            {
                os << ",armorRating=" << item.armorRating();
            }

            if ((item.damageMin() != 0) || (item.damageMax() != 0))
            {
                os << ",damage=" << item.damageMin() << '-' << item.damageMax();
            }

            if (item.isMisc())
            {
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
            }

            os << ",value=" << item.value();

            os << ']';
            return os;
        }

    } // namespace item

} // namespace castlecrawl
