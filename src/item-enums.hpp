#ifndef CASTLECRAWL_ITEM_ENUMS_HPP_INCLUDED
#define CASTLECRAWL_ITEM_ENUMS_HPP_INCLUDED
//
// item-enums.hpp
//
#include <string>

#include <SFML/System/Vector2.hpp>

namespace castlecrawl
{
    namespace item
    {

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

        inline const std::string weaponName(const Weapon weapon)
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

        inline const sf::Vector2i baseWeaponDamage(const Weapon weapon)
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

        inline const std::string weaponMaterialName(const WeaponMaterial material)
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

        inline int weaponMaterialDamage(const WeaponMaterial material)
        {
            // clang-format off
            switch (material)
            {
                case WeaponMaterial::Bronze:    { return -1; }
                case WeaponMaterial::Steel:     { return  0; }
                case WeaponMaterial::Obsidian:  { return  2; }
                case WeaponMaterial::Silver:    { return  4; }
                case WeaponMaterial::Gold:      { return  8; }
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

        inline const std::string armorName(const Armor armor)
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

        inline int baseArmorRating(const Armor armor)
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

        inline const std::string armorMaterialName(const ArmorMaterial material)
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

        inline int armorMaterialRating(const ArmorMaterial material)
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

        inline const std::string miscName(const Misc misc)
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
        inline std::size_t miscEquipCount(const Misc misc)
        {
            // clang-format off
            switch (misc)
            {
                case Misc::Amulet:    { return 1; }
                case Misc::Potion:    { return 0; }
                case Misc::Ring:      { return 2; }
                case Misc::Charm:     { return 1; }
                case Misc::Mask:      { return 1; }
                case Misc::Talisman:  { return 1; }
                case Misc::Herbs:     { return 0; }
                case Misc::Count:
                default:              { return 1; }
            }
            // clang-format on
        }

        inline bool isMiscEquipable(const Misc misc) { return (miscEquipCount(misc) > 0); }

        // misc items are either Useable or Equipable but never both and never neither
        inline bool isMiscUseable(const Misc misc) { return !isMiscEquipable(misc); }

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

        // useable misc items (potions & herbs) can only have the "Magic" material
        inline MiscMaterial requiredMiscMaterial(const Misc misc)
        {
            MiscMaterial material = MiscMaterial::Count;

            if (isMiscUseable(misc))
            {
                material = MiscMaterial::Magic;
            }

            return material;
        }

        inline const std::string miscMaterialName(const MiscMaterial material)
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

        inline int miscMaterialValue(const MiscMaterial material)
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

        inline const std::string useStrengthName(const UseStrength strength)
        {
            // clang-format off
            switch (strength)
            {
                case UseStrength::Weak:     { return "Weak"; }
                case UseStrength::Strong:   { return "Strong"; }
                case UseStrength::Normal://don't let the word 'normal' in item names
                default:                    { return ""; }
            }
            // clang-format on
        }

    } // namespace item
} // namespace castlecrawl

#endif // CASTLECRAWL_ITEM_ENUMS_HPP_INCLUDED
