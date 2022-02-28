// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// item-factory.cpp
//
#include "item-factory.hpp"

#include "check-macros.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

namespace castlecrawl
{
    namespace item
    {

        ItemFactory::ItemFactory() { validateAndOutputAll(); }

        void ItemFactory::validateAndOutputAll()
        {
            std::vector<Item> items;

            for (int i = 0; i < static_cast<int>(Weapon::Count); ++i)
            {
                const auto type = static_cast<Weapon>(i);
                for (int m = 0; m < static_cast<int>(WeaponMaterial::Count); ++m)
                {
                    const auto material = static_cast<WeaponMaterial>(m);
                    items.push_back(Item(type, material));
                }
            }

            for (int i = 0; i < static_cast<int>(Armor::Count); ++i)
            {
                const auto type = static_cast<Armor>(i);
                for (int m = 0; m < static_cast<int>(ArmorMaterial::Count); ++m)
                {
                    const auto material = static_cast<ArmorMaterial>(m);
                    items.push_back(Item(type, material));
                }
            }

            for (int i = 0; i < static_cast<int>(Misc::Count); ++i)
            {
                const auto type = static_cast<Misc>(i);
                if (hasMiscMaterial(type))
                {
                    for (int m = 0; m < static_cast<int>(MiscMaterial::Count); ++m)
                    {
                        const auto material = static_cast<MiscMaterial>(m);
                        items.push_back(Item(type, material));
                    }
                }
                else
                {
                    items.push_back(Item(type, MiscMaterial::Count));
                }
            }

            std::sort(std::begin(items), std::end(items), [](const Item & A, const Item & B) {
                return (A.value() < B.value());
            });

            std::cout << items.size() << " items" << std::endl << std::endl;

            for (const Item & item : items)
            {
                validateItem(item);
            }

            for (const Item & item : items)
            {
                std::cout << '\t' << item.value() << "\t" << item << std::endl;
            }

            std::cout << std::endl;

            for (const Item & item : items)
            {
                std::cout << '\t' << item.description() << std::endl;
            }
        }

        void ItemFactory::validateItem(const Item & item)
        {
            {
                std::size_t count = 0;
                if (item.isArmor())
                {
                    ++count;
                }

                if (item.isWeapon())
                {
                    ++count;
                }

                if (item.isMisc())
                {
                    ++count;
                }

                M_CHECK(
                    (count == 1),
                    "Error:  Item's basic type of Weapon/Armor/Misc count is "
                        << count << " (not essential and mutually exclusive): " << item);
            }

            M_CHECK(!item.name().empty(), "Error:  Item has no name: " << item);

            if (item.isUseable())
            {
                M_CHECK(!item.isEquipable(), "Error:  Item is Useable and Equipable: " << item);
            }

            if (item.isEquipable())
            {
                M_CHECK(!item.isUseable(), "Error:  Item is Equipable and Useable: " << item);
            }

            if (item.isArmor())
            {
                M_CHECK(
                    (item.armorRating() >= 1),
                    "Error:  Armor Item's amor_rating invalid: " << item);

                M_CHECK(
                    (item.armorMaterial() != ArmorMaterial::Count),
                    "Error:  Armor Item has no material: " << item);

                M_CHECK(
                    item.isEquipable(),
                    "Error:  Armor Item SHOULD be Equipable but is not: " << item);
            }

            if (item.isWeapon())
            {
                M_CHECK(
                    (item.damageMin() > 0), "Error:  Weapon Item's damage_min invalid: " << item);

                M_CHECK(
                    (item.damageMax() > item.damageMin()),
                    "Error:  Weapon Item's damage_max is not greater than the min: " << item);

                M_CHECK(
                    (item.weaponMaterial() != WeaponMaterial::Count),
                    "Error:  Weapon Item has no material: " << item);

                M_CHECK(
                    item.isEquipable(),
                    "Error:  Weapon Item SHOULD be Equipable but is not: " << item);
            }

            if (item.isMisc())
            {
                if (hasMiscMaterial(item.miscType()))
                {
                    M_CHECK(
                        (item.miscMaterial() != MiscMaterial::Count),
                        "Error: Misc item SHOULD have a material: " << item);
                }
                else
                {
                    M_CHECK(
                        (item.miscMaterial() == MiscMaterial::Count),
                        "Error: Misc item should NOT have a material: " << item);
                }
            }

            M_CHECK((item.value() > 0), "Error:  Item's Value is zero or less: " << item)
        }

    } // namespace item

} // namespace castlecrawl
