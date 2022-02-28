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
                if (requiredMiscMaterial(type) == MiscMaterial::Count)
                {
                    for (int m = 0; m < static_cast<int>(MiscMaterial::Magic); ++m)
                    {
                        const auto material = static_cast<MiscMaterial>(m);
                        items.push_back(Item(type, material, UseStrength::Normal, {}, {}));
                    }
                }
                else
                {
                    items.push_back(Item(type, MiscMaterial::Magic, UseStrength::Weak, {}, {}));
                    items.push_back(Item(type, MiscMaterial::Magic, UseStrength::Normal, {}, {}));
                    items.push_back(Item(type, MiscMaterial::Magic, UseStrength::Strong, {}, {}));
                }
            }

            std::sort(std::begin(items), std::end(items));

            for (const Item & item : items)
            {
                validateItem(item);
            }
            
            std::string longestName;
            std::string longestDesc;
            for (const Item & item : items)
            {
                if (item.name().size() > longestName.size())
                {
                    longestName = item.name();
                }

                if (item.description().size() > longestDesc.size())
                {
                    longestDesc = item.description();
                }
            }

            std::cout << std::endl;

            for (const Item & item : items)
            {
                std::cout << '\t' << item.description() << '\n';
            }

            std::cout << std::endl;

            for (const Item & item : items)
            {
                std::cout << '\t' << item.value() << "\t" << item << '\n';
            }

            std::cout << items.size() << " items total" << std::endl << std::endl;

            std::cout << "longest name and description:\n\t" << longestName << ": "
                      << longestName.size() << "\n\t" << longestDesc << ": " << longestDesc.size()
                      << std::endl;

            std::cout << std::endl;
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
                if ((item.miscType() == Misc::Potion) || (item.miscType() == Misc::Herbs))
                {
                    M_CHECK(
                        (item.miscMaterial() == MiscMaterial::Magic),
                        "Error: Misc item Potions and Herbs MUST have the material 'Magic': "
                            << item);
                }
                else
                {
                    M_CHECK(
                        (item.miscMaterial() != MiscMaterial::Magic),
                        "Error: This Misc item must NOT have the material 'Magic': " << item);
                }
            }

            M_CHECK((item.value() > 0), "Error:  Item's Value is zero or less: " << item)
        }

    } // namespace item

} // namespace castlecrawl
