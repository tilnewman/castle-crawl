#ifndef CASTLECRAWL_ITEM_FACTORY_HPP_INCLUDED
#define CASTLECRAWL_ITEM_FACTORY_HPP_INCLUDED
//
// item-factory.hpp
//
#include "item.hpp"

namespace castlecrawl
{
    namespace item
    {

        class ItemFactory
        {
          public:
            ItemFactory();

          private:
            const ItemVec_t makeAll() const;
            const ItemVec_t makeWeapons() const;
            const ItemVec_t makeArmor() const;
            const ItemVec_t makeMisc() const;
            const ItemVec_t makeCustom() const;

            void validateAndDumpToConsole() const;
            void validate(const Item & item) const;
        };

    } // namespace item
} // namespace castlecrawl

#endif // CASTLECRAWL_ITEM_FACTORY_HPP_INCLUDED
