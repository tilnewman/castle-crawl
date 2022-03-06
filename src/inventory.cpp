// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// inventory.cpp
//
#include "inventory.hpp"

#include "check-macros.hpp"

namespace castlecrawl
{
    namespace item
    {

        Inventory::Inventory()
            : m_items()
        {}

        void Inventory::add(const ItemVec_t & items)
        {
            for (const Item & item : items)
            {
                m_items.push_back(item);
            }
        }

        void Inventory::remove(const std::size_t index)
        {
            M_CHECK(index < m_items.size(), "Error:  Tried to remove() out of bounds index!");
            m_items.erase(std::begin(m_items) + static_cast<std::ptrdiff_t>(index));
        }

        const std::string Inventory::equip(const std::size_t index)
        {
            M_CHECK(index < m_items.size(), "Error:  Tried to equip() out of bounds index!");

            const Item & item = m_items[index];

            if (item.isWeapon() && hasWeaponEquipped())
            {
                return "Already has a weapon equipped.";
            }
            else if (item.isArmor())
            {
                if (hasEquipped(item.armorType()))
                {
                    std::string str;
                    str += "Already has ";
                    str += toString(item.armorType());
                    str += " equipped.";
                    return str;
                }
            }
            else if (item.isMisc())
            {
                if (!isMiscEquipable(item.miscType()))
                {
                    std::string str;
                    str += toString(item.miscType());
                    str += " can't be equipped.";
                    return str;
                }

                const std::size_t count = miscEquipCount(item.miscType());
                if (countOfEquipped(item.miscType()) >= count)
                {
                    std::string str;
                    str += "Already has ";
                    str += std::to_string(count);
                    str += " equipped.";
                    return str;
                }
            }

            m_eqItems.push_back(m_items[index]);
            m_items.erase(std::begin(m_items) + static_cast<std::ptrdiff_t>(index));
            return "";
        }

        void Inventory::unequip(const std::size_t index)
        {
            M_CHECK(index < m_eqItems.size(), "Error:  Tried to unequip() out of bounds index!");
            m_items.push_back(m_eqItems[index]);
            m_eqItems.erase(std::begin(m_eqItems) + static_cast<std::ptrdiff_t>(index));
        }

        const EquipEffect Inventory::totalEquipEffects() const
        {
            EquipEffect equipEffect;

            for (const Item & item : m_eqItems)
            {
                equipEffect += item.equipEffect();
            }

            return equipEffect;
        }

        int Inventory::armorRating() const
        {
            int armorRating = 0;

            for (const Item & item : m_eqItems)
            {
                if (item.isArmor())
                {
                    armorRating += item.armorRating();
                }
            }

            return armorRating;
        }

        bool Inventory::hasWeaponEquipped() const
        {
            for (const Item & item : m_eqItems)
            {
                if (item.isWeapon())
                {
                    return true;
                }
            }

            return false;
        }

        bool Inventory::hasEquipped(const Armor armor) const
        {
            for (const Item & item : m_eqItems)
            {
                if (item.armorType() == armor)
                {
                    return true;
                }
            }

            return false;
        }

        std::size_t Inventory::countOfEquipped(const Misc misc) const
        {
            std::size_t count = 0;

            for (const Item & item : m_eqItems)
            {
                if (item.miscType() == misc)
                {
                    ++count;
                }
            }

            return count;
        }

    } // namespace item

} // namespace castlecrawl
