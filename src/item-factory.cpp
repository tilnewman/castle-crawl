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
#include <set>

namespace castlecrawl
{
    namespace item
    {

        ItemFactory::ItemFactory() { validateAndDumpToConsole(); }


        const ItemVec_t ItemFactory::makeAll() const 
        {
            ItemVec_t items;

            for (const Item & item : makeWeapons())
            {
                items.push_back(item);
            }

            for (const Item & item : makeArmor())
            {
                items.push_back(item);
            }

            for (const Item & item : makeMisc())
            {
                items.push_back(item);
            }

            for (const Item & item : makeCustom())
            {
                items.push_back(item);
            }

            return items;
        }
        
        const ItemVec_t ItemFactory::makeWeapons() const 
        {
            ItemVec_t items;

            for (int i = 0; i < static_cast<int>(Weapon::Count); ++i)
            {
                const auto type = static_cast<Weapon>(i);
                for (int m = 0; m < static_cast<int>(WeaponMaterial::Count); ++m)
                {
                    const auto material = static_cast<WeaponMaterial>(m);
                    items.push_back(Item(type, material));
                }
            }

            return items;
        }

        const ItemVec_t ItemFactory::makeArmor() const 
        {
            ItemVec_t items;

            for (int i = 0; i < static_cast<int>(Armor::Count); ++i)
            {
                const auto type = static_cast<Armor>(i);
                for (int m = 0; m < static_cast<int>(ArmorMaterial::Count); ++m)
                {
                    const auto material = static_cast<ArmorMaterial>(m);
                    items.push_back(Item(type, material));
                }
            }

            return items;
        }

        const ItemVec_t ItemFactory::makeMisc() const 
        {
            ItemVec_t items;

            // these are the equipable misc items
            for (int i = 0; i < static_cast<int>(Misc::Count); ++i)
            {
                const auto type = static_cast<Misc>(i);
                if (requiredMiscMaterial(type) != MiscMaterial::Count)
                {
                    continue;
                }

                for (int m = 0; m < static_cast<int>(MiscMaterial::Magic); ++m)
                {
                    const auto material = static_cast<MiscMaterial>(m);

                    items.push_back(Item(
                        type,
                        material,
                        UseStrength::Normal,
                        {},
                        miscMaterialEquipEffect(material)));
                }
            }

            // these are the useable misc items
            // clang-format off
            items.push_back(Item(Misc::Potion, MiscMaterial::Magic, UseStrength::Weak,   {.health=8}, {}));
            items.push_back(Item(Misc::Potion, MiscMaterial::Magic, UseStrength::Normal, {.health=16}, {}));
            items.push_back(Item(Misc::Potion, MiscMaterial::Magic, UseStrength::Strong, {.health=32}, {}));
            //
            items.push_back(Item(Misc::Potion, MiscMaterial::Magic, UseStrength::Weak,   {.mana=5}, {}));
            items.push_back(Item(Misc::Potion, MiscMaterial::Magic, UseStrength::Normal, {.mana=10}, {}));
            items.push_back(Item(Misc::Potion, MiscMaterial::Magic, UseStrength::Strong, {.mana=20}, {}));
            //
            items.push_back(Item(Misc::Herbs, MiscMaterial::Magic, UseStrength::Weak,   {.health=5}, {}));
            items.push_back(Item(Misc::Herbs, MiscMaterial::Magic, UseStrength::Normal, {.health=10}, {}));
            items.push_back(Item(Misc::Herbs, MiscMaterial::Magic, UseStrength::Strong, {.health=20}, {}));
            // clang-format on

            return items;
        }


        const ItemVec_t ItemFactory::makeCustom() const 
        {
            ItemVec_t items;

            // custom magical items (must have a unique name) (lots more todo here)
            for (int i = 0; i < static_cast<int>(Weapon::Count); ++i)
            {
                const auto type = static_cast<Weapon>(i);

                items.push_back(Item(
                    type,
                    WeaponMaterial::Obsidian,
                    std::string(weaponName(type)).append(" of Night"),
                    { .arc = 3, .dmg = 3 }));
            }

            items.push_back(
                Item(Weapon::Dagger, WeaponMaterial::Steel, "Backstabber Dagger", { .dmg = 7 }));

            for (int i = 0; i < static_cast<int>(Armor::Count); ++i)
            {
                const auto type = static_cast<Armor>(i);

                items.push_back(Item(
                    type,
                    ArmorMaterial::DragonScale,
                    std::string("Dragon Slayer ").append(armorName(type)),
                    { .arc = 5, .dmg = 5, .str = 5 }));
            }

            return items;
        }

        void ItemFactory::validateAndDumpToConsole() const
        {
            ItemVec_t items{ makeAll() };

            std::sort(std::begin(items), std::end(items));

            for (const Item & item : items)
            {
                validate(item);
            }
            
            std::set<std::string> names;
            std::string longestName;
            std::string longestDesc;
            for (const Item & item : items)
            {
                const std::string name = item.name();

                const auto iter = names.find(name);
                if (iter != std::end(names))
                {
                    std::cout << "Error: Two items had the same name: " << item << '\n';
                }
                else
                {
                    names.insert(name);
                }

                if (name.size() > longestName.size())
                {
                    longestName = name;
                }

                const std::string desc = item.description();
                if (desc.size() > longestDesc.size())
                {
                    longestDesc = desc;
                }
            }

            std::cout << std::endl << "All Descriptions:" << std::endl;
           
            for (const Item & item : items)
            {
                std::cout << '\t' << item.description() << '\n';
            }

            std::cout << std::endl << "All Non-Magical:" << std::endl;

            for (const Item & item : items)
            {
                if (!item.isMagical())
                {
                    std::cout << '\t' << item.value() << "\t" << item << '\n';
                }
            }

            std::cout << std::endl << "All Useable Names:" << std::endl;
            
            for (const Item & item : items)
            {
                if (item.isUseable())
                {
                    std::cout << '\t' << item.value() << "\t" << item.name() << '\n';
                }
            }

            std::cout << std::endl << "All Magical Weapons and Armor:" << std::endl;

            for (const Item & item : items)
            {
                if (!item.isMagical())
                {
                    continue;
                }

                if (item.isWeapon() || item.isArmor())
                {
                    std::cout << "\t" << item.value() << "\t" << item.description() << '\n';
                }
            }

            std::cout << std::endl;

            std::cout << items.size() << " items total" << std::endl << std::endl;

            std::cout << "longest name and description:\n\t" << longestName << ": "
                      << longestName.size() << "\n\t" << longestDesc << ": " << longestDesc.size()
                      << std::endl
                      << std::endl;

           
            json j = items.back();
            std::cout << "JSON: " << j << std::endl;
        }

        void ItemFactory::validate(const Item & item) const
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

                if (item.isMagical())
                {
                    M_CHECK(
                        (item.name() != armorName(item.armorType())),
                        "Error: Magical armor has a default name:" << item);

                    M_CHECK(
                        (item.equipEffect().total() > 0),
                        "Error: Magical armor has no equip effect:" << item);
                }
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

                if (item.isMagical())
                {
                    M_CHECK(
                        (item.name() != weaponName(item.weaponType())),
                        "Error: Magical weapon has a default name:" << item);

                    M_CHECK(
                        (item.equipEffect().total() > 0),
                        "Error: Magical weapon has no equip effect:" << item);
                }
            }

            if (item.isMisc())
            {
                if (item.isUseable())
                {
                    M_CHECK(
                        (item.useEffect().total() > 0),
                        "Error:  Useable item has no use effects: " << item);

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

            M_CHECK((item.value() > 0), "Error:  Item's Value is zero or less: " << item);

            json j = item;
            const Item item2 = j.get<Item>();
            M_CHECK((item == item2), "Error:  Item failed to json serialize correctly: " << item);
        }

    } // namespace item

} // namespace castlecrawl
