// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// item-factory.cpp
//
#include "item-factory.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

namespace castlecrawl
{
    namespace item
    {

        ItemFactory::ItemFactory() {}

        void ItemFactory::dumpInfo()
        {
            std::vector<Item> items;

            for (int i = 1; i < static_cast<int>(Weapon::Count); ++i)
            {
                const auto type = static_cast<Weapon>(i);
                items.push_back(Item(weaponName(type), type));
            }

            for (int i = 1; i < static_cast<int>(Armor::Count); ++i)
            {
                const auto type = static_cast<Armor>(i);
                items.push_back(Item(armorName(type), type));
            }

            for (int i = 1; i < static_cast<int>(Misc::Count); ++i)
            {
                const auto type = static_cast<Misc>(i);
                items.push_back(Item(miscName(type), type));
            }

            std::sort(std::begin(items), std::end(items), [](const Item & A, const Item & B) {
                return (A.value() < B.value());
            });

            for (const Item & item : items)
            {
                std::cout << '\t' << item.value() << "\t\t" << item.name() << std::endl;
            }
        }

    } // namespace item

} // namespace castlecrawl
