#ifndef CASTLECRAWL_Inventory_HPP_INCLUDED
#define CASTLECRAWL_Inventory_HPP_INCLUDED
//
// inventory.hpp
//
#include "item.hpp"

#include <vector>

namespace castlecrawl
{
    namespace item
    {

        class Inventory
        {
        public:
            Inventory();

            void add(const Item & item) { m_items.push_back(item); }
            void remove(const std::size_t index);

            const std::string equip(const std::size_t index);
            void unequip(const std::size_t index);

            const auto items() const { return m_items; }
            const auto eqItems() const { return m_eqItems; }

            const EquipEffect totalEquipEffects() const;

        private:
            bool hasWeaponEquipped() const;
            bool hasEquipped(const Armor armor) const;
            std::size_t countOfEquipped(const Misc misc) const;

        private:
            std::vector<Item> m_items;
            std::vector<Item> m_eqItems;
        };

    } // namespace item
} // namespace castlecrawl

#endif // CASTLECRAWL_INVENTORY_HPP_INCLUDED
