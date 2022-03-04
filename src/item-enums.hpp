#ifndef CASTLECRAWL_ITEM_ENUMS_HPP_INCLUDED
#define CASTLECRAWL_ITEM_ENUMS_HPP_INCLUDED
//
// item-enums.hpp
//
#include <compare>
#include <string>

#include <SFML/System/Vector2.hpp>

#include "json.hpp"

namespace castlecrawl
{
    using json = nlohmann::json;

    namespace item
    {

        struct UseEffect
        {
            int health = 0;
            int mana = 0;

            constexpr int total() const noexcept { return (health + mana); }
            constexpr bool empty() const noexcept { return (total() == 0); }
            auto operator<=>(const UseEffect &) const = default;
        };

        inline void to_json(json & j, const UseEffect & ue)
        {
            j = json{ { "health", ue.health }, { "mana", ue.mana } };
        }

        inline void from_json(const json & j, UseEffect & ue)
        {
            j.at("health").get_to(ue.health);
            j.at("mana").get_to(ue.mana);
        }

        //

        struct EquipEffect
        {
            int acc = 0;
            int arc = 0;
            int dex = 0;
            int dmg = 0;
            int lck = 0;
            int str = 0;

            constexpr int total() const noexcept { return (str + dex + arc + lck + dmg); }
            constexpr bool empty() const noexcept { return (total() == 0); }

            constexpr inline EquipEffect & operator+=(const EquipEffect & right) noexcept
            {
                acc += right.acc;
                arc += right.arc;
                dex += right.dex;
                dmg += right.dmg;
                lck += right.lck;
                str += right.str;
                return *this;
            }

            friend constexpr inline EquipEffect
                operator+(EquipEffect left, const EquipEffect & right) noexcept
            {
                left += right;
                return left;
            }

            auto operator<=>(const EquipEffect &) const = default;
        };

        inline void to_json(json & j, const EquipEffect & ee)
        {
            // clang-format off
            j = json{ { "acc", ee.acc }, 
                      { "arc", ee.arc },
                      { "dex", ee.dex },
                      { "dmg", ee.dmg },
                      { "lck", ee.lck },
                      { "str", ee.str } };
            // clang-format on
        }

        inline void from_json(const json & j, EquipEffect & ee)
        {
            j.at("acc").get_to(ee.acc);
            j.at("arc").get_to(ee.arc);
            j.at("dex").get_to(ee.dex);
            j.at("dmg").get_to(ee.dmg);
            j.at("lck").get_to(ee.lck);
            j.at("str").get_to(ee.str);
        }

        //

        enum class Weapon
        {
            Dagger = 0,
            Handaxe,
            Mace,
            Warhammer,
            Shortsword,
            Longsword,
            Claymore,
            Waraxe,
            Scythe,
            Count
        };

        inline constexpr std::string_view toString(const Weapon weapon) noexcept
        {
            // clang-format off
            switch (weapon)
            {
                case Weapon::Dagger:        { return "Dagger"; }
                case Weapon::Handaxe:       { return "Handaxe"; }
                case Weapon::Mace:          { return "Mace"; }
                case Weapon::Warhammer:     { return "Warhammer"; }
                case Weapon::Shortsword:    { return "Shortsword"; }
                case Weapon::Longsword:     { return "Longsword"; }
                case Weapon::Claymore:      { return "Claymore"; }
                case Weapon::Waraxe:        { return "Waraxe"; }
                case Weapon::Scythe:        { return "Scythe"; }
                case Weapon::Count:
                default:                    { return ""; }
            }
            // clang-format on
        }

        inline const sf::Vector2i baseWeaponDamage(const Weapon weapon) noexcept
        {
            // clang-format off
            switch (weapon)
            {
                case Weapon::Dagger:     { return {  2,  4 }; }
                case Weapon::Handaxe:    { return {  3,  6 }; }
                case Weapon::Mace:       { return {  9, 13 }; }
                case Weapon::Warhammer:  { return { 10, 16 }; }
                case Weapon::Shortsword: { return {  6, 10 }; }
                case Weapon::Longsword:  { return {  9, 13 }; }
                case Weapon::Claymore:   { return { 10, 16 }; }
                case Weapon::Waraxe:     { return { 12, 18 }; }
                case Weapon::Scythe:     { return { 13, 20 }; }
                case Weapon::Count:
                default:                 { return {  0,  0 }; }
            }
            // clang-format on
        }

        enum class WeaponMaterial
        {
            Bronze = 0,
            Steel,
            Obsidian,
            Silver,
            Gold,
            Count
        };

        inline constexpr std::string_view toString(const WeaponMaterial material) noexcept
        {
            // clang-format off
            switch (material)
            {
                case WeaponMaterial::Bronze:    { return "Bronze"; }
                case WeaponMaterial::Steel:     { return "Steel"; }
                case WeaponMaterial::Obsidian:  { return "Obsidian"; }
                case WeaponMaterial::Silver:    { return "Silver"; }
                case WeaponMaterial::Gold:      { return "Gold"; }
                case WeaponMaterial::Count:
                default:                        { return ""; }
            }
            // clang-format on
        }

        inline constexpr int weaponMaterialDamage(const WeaponMaterial material) noexcept
        {
            // clang-format off
            switch (material)
            {
                case WeaponMaterial::Bronze:    { return 0; }
                case WeaponMaterial::Steel:     { return 1; }
                case WeaponMaterial::Obsidian:  { return 4; }
                case WeaponMaterial::Silver:    { return 6; }
                case WeaponMaterial::Gold:      { return 8; }
                case WeaponMaterial::Count:
                default:                        { return 0; }
            }
            // clang-format on
        }

        enum class Armor
        {
            Helm = 0,
            Cuirass,
            Bracers,
            Gauntlets,
            Greaves,
            Boots,
            Count
        };

        inline constexpr std::string_view toString(const Armor armor) noexcept
        {
            // clang-format off
            switch (armor)
            {
                case Armor::Helm:       { return "Helm"; }
                case Armor::Cuirass:    { return "Cuirass"; }
                case Armor::Bracers:    { return "Bracers"; }
                case Armor::Gauntlets:  { return "Gauntlets"; }
                case Armor::Greaves:    { return "Greaves"; }
                case Armor::Boots:      { return "Boots"; }
                case Armor::Count:
                default:                { return ""; }
            }
            // clang-format on
        }

        inline constexpr int baseArmorRating(const Armor armor) noexcept
        {
            // clang-format off
            switch (armor)
            {
                case Armor::Helm:       { return 5; }
                case Armor::Cuirass:    { return 9; }
                case Armor::Bracers:    { return 3; }
                case Armor::Gauntlets:  { return 2; }
                case Armor::Greaves:    { return 6; }
                case Armor::Boots:      { return 1; }
                case Armor::Count:
                default:                { return 0; }
            }
            // clang-format on
        }

        enum class ArmorMaterial
        {
            Leather = 0,
            Bronze,
            Steel,
            Silver,
            Gold,
            DragonScale,
            Count
        };

        inline constexpr std::string_view toString(const ArmorMaterial material) noexcept
        {
            // clang-format off
            switch (material)
            {
                case ArmorMaterial::Leather:    { return "Leather"; }
                case ArmorMaterial::Bronze:     { return "Bronze"; }
                case ArmorMaterial::Steel:      { return "Steel"; }
                case ArmorMaterial::Silver:     { return "Silver"; }
                case ArmorMaterial::Gold:       { return "Gold"; }
                case ArmorMaterial::DragonScale:{ return "Dragon Scale"; }
                case ArmorMaterial::Count:
                default:                        { return ""; }
            }
            // clang-format on
        }

        inline constexpr int armorMaterialRating(const ArmorMaterial material) noexcept
        {
            // clang-format off
            switch (material)
            {
                case ArmorMaterial::Leather:    { return 0; }
                case ArmorMaterial::Bronze:     { return 1; }
                case ArmorMaterial::Steel:      { return 2; }
                case ArmorMaterial::Silver:     { return 4; }
                case ArmorMaterial::Gold:       { return 6; }
                case ArmorMaterial::DragonScale:{ return 9; }
                case ArmorMaterial::Count:
                default:                        { return 0; }
            }
            // clang-format on
        }

        // there are only equipable and useable misc items
        enum class Misc
        {
            Amulet = 0,
            Ring,
            Charm,
            Mask,
            Talisman,
            Potion,
            Herbs,
            Count
        };

        inline constexpr std::string_view toString(const Misc misc) noexcept
        {
            // clang-format off
            switch (misc)
            {
                case Misc::Amulet:      { return "Amulet"; }
                case Misc::Potion:      { return "Potion"; }
                case Misc::Ring:        { return "Ring"; }
                case Misc::Charm:       { return "Charm"; }
                case Misc::Mask:        { return "Mask"; }
                case Misc::Talisman:    { return "Talisman"; }
                case Misc::Herbs:       { return "Herbs"; }
                case Misc::Count:
                default:                { return ""; }
            }
            // clang-format on
        }

        // if not misc, then it's either weapon/armor which can only equip one of
        inline constexpr std::size_t miscEquipCount(const Misc misc) noexcept
        {
            // clang-format off
            switch (misc)
            {
                case Misc::Amulet:    { return 1; }
                case Misc::Potion:    { return 0; }
                case Misc::Ring:      { return 4; }
                case Misc::Charm:     { return 1; }
                case Misc::Mask:      { return 1; }
                case Misc::Talisman:  { return 1; }
                case Misc::Herbs:     { return 0; }
                case Misc::Count:
                default:              { return 1; }
            }
            // clang-format on
        }

        inline constexpr bool isMiscEquipable(const Misc misc) noexcept
        {
            return (miscEquipCount(misc) > 0);
        }

        // misc items are either Useable or Equipable but never both and never neither
        inline constexpr bool isMiscUseable(const Misc misc) noexcept
        {
            return !isMiscEquipable(misc);
        }

        enum class MiscMaterial
        {
            Iron = 0,
            Bronze,
            Bone,
            Tribal,
            Fang,
            Jade,
            Obsidian,
            Lazuli,
            Bloody,
            Jeweled,
            Magic,
            Count
        };

        inline constexpr EquipEffect miscMaterialEquipEffect(const MiscMaterial material) noexcept
        {
            // clang-format off
            switch (material)
            {
                case MiscMaterial::Iron:     { return { .str=3 }; }
                case MiscMaterial::Bronze:   { return { .str=1 }; }
                case MiscMaterial::Bone:     { return { .arc=1, .dmg=1 }; }
                case MiscMaterial::Tribal:   { return { .arc=3, .lck=1 }; }
                case MiscMaterial::Fang:     { return { .dmg=5 }; }
                case MiscMaterial::Jade:     { return { .lck=5 }; }
                case MiscMaterial::Obsidian: { return { .arc=3, .dmg=3 }; }
                case MiscMaterial::Lazuli:   { return { .arc=5, .lck=3 }; }
                case MiscMaterial::Bloody:   { return { .dmg=10 }; }
                case MiscMaterial::Jeweled:  { return { .arc=10, .lck=5 }; }
                case MiscMaterial::Magic:
                case MiscMaterial::Count:
                default:                     { return {}; }
            }
            // clang-format on
        }

        // useable misc items (potions & herbs) can only have the "Magic" material
        inline constexpr MiscMaterial requiredMiscMaterial(const Misc misc) noexcept
        {
            MiscMaterial material = MiscMaterial::Count;

            if (isMiscUseable(misc))
            {
                material = MiscMaterial::Magic;
            }

            return material;
        }

        inline constexpr std::string_view toString(const MiscMaterial material) noexcept
        {
            // clang-format off
            switch (material)
            {
                case MiscMaterial::Bone:        { return "Bone"; }
                case MiscMaterial::Fang:        { return "Fang"; }
                case MiscMaterial::Obsidian:    { return "Obsidian"; }
                case MiscMaterial::Bronze:      { return "Bronze"; }
                case MiscMaterial::Jade:        { return "Jade"; }
                case MiscMaterial::Lazuli:      { return "Lazuli"; }
                case MiscMaterial::Bloody:      { return "Bloody"; }
                case MiscMaterial::Tribal:      { return "Tribal"; }
                case MiscMaterial::Jeweled:     { return "Jeweled"; }
                case MiscMaterial::Iron:        { return "Iron"; }
                case MiscMaterial::Magic:       { return "Magic"; }
                case MiscMaterial::Count:
                default:                        { return ""; }
            }
            // clang-format on
        }

        inline constexpr int miscMaterialValue(const MiscMaterial material) noexcept
        {
            // clang-format off
            switch (material)
            {
                case MiscMaterial::Iron:        { return 0; }
                case MiscMaterial::Bronze:      { return 1; }
                case MiscMaterial::Bone:        { return 2; }
                case MiscMaterial::Tribal:      { return 3; }
                case MiscMaterial::Fang:        { return 4; }
                case MiscMaterial::Jade:        { return 5; }
                case MiscMaterial::Obsidian:    { return 6; }
                case MiscMaterial::Lazuli:      { return 7; }
                case MiscMaterial::Bloody:      { return 8; }
                case MiscMaterial::Jeweled:     { return 9; }
                case MiscMaterial::Magic:       { return 0; }
                case MiscMaterial::Count:
                default:                        { return 0; }
            }
            // clang-format on
        }

        enum class UseStrength
        {
            Weak,
            Normal,
            Strong
        };

        inline constexpr std::string_view toString(const UseStrength strength) noexcept
        {
            // clang-format off
            switch (strength)
            {
                case UseStrength::Weak:     { return "Weak"; }
                case UseStrength::Strong:   { return "Strong"; }
                case UseStrength::Normal://don't let the word 'normal' appear in item names
                default:                    { return ""; }
            }
            // clang-format on
        }

    } // namespace item
} // namespace castlecrawl

#endif // CASTLECRAWL_ITEM_ENUMS_HPP_INCLUDED
