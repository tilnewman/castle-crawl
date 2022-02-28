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
            void validateAndOutputAll();
            void validateItem(const Item & item);
        };

    } // namespace item
} // namespace castlecrawl

#endif // CASTLECRAWL_ITEM_FACTORY_HPP_INCLUDED