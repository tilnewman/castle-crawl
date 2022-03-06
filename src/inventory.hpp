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
            void add(const ItemVec_t & items);
            void remove(const std::size_t index);

            const std::string equip(const std::size_t index);
            void unequip(const std::size_t index);

            ItemVec_t & unItems() { return m_items; }
            ItemVec_t & eqItems() { return m_eqItems; }

            const EquipEffect totalEquipEffects() const;
            int armorRating() const;

            friend void to_json(json & j, const Inventory & i);
            friend void from_json(const json & j, Inventory & i);

          private:
            bool hasWeaponEquipped() const;
            bool hasEquipped(const Armor armor) const;
            std::size_t countOfEquipped(const Misc misc) const;

          private:
            ItemVec_t m_items;
            ItemVec_t m_eqItems;
        };

        inline void to_json(json & j, const Inventory & inv)
        {
            j = json{ { "items", inv.m_items }, { "equipped_items", inv.m_eqItems } };
        }

        inline void from_json(const json & j, Inventory & inv)
        {
            j.at("items").get_to(inv.m_items);
            j.at("equipped_items").get_to(inv.m_eqItems);
        }

    } // namespace item
} // namespace castlecrawl

#endif // CASTLECRAWL_INVENTORY_HPP_INCLUDED
