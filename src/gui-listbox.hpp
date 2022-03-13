#ifndef CASTLECRAWL_GUI_LISTBOX_HPP_INCLUDED
#define CASTLECRAWL_GUI_LISTBOX_HPP_INCLUDED
//
// gui-listbox.hpp
//
#include "item.hpp"
#include "media.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Vertex.hpp>

namespace sf
{
    class RenderTarget;
} // namespace sf

namespace castlecrawl
{
    struct Context;

    struct ListboxIndex
    {
        std::size_t display = 0;
        std::size_t offset = 0;
    };

    //

    class Listbox : public sf::Drawable
    {
      public:
        Listbox(const item::ItemVec_t & items);

        void setupSize(
            const Context & context,
            const FontSize fontSize,
            const std::size_t widthCharsMax,
            const std::size_t heightRows);

        bool empty() const { return m_items.empty(); }

        bool hasFocus() const { return m_hasFocus; }
        void setFocus(const bool hasFocus);

        std::size_t selectedIndex() const { return (m_indexes.display + m_indexes.offset); }

        const sf::FloatRect getGlobalBounds() const { return m_bgRectangle.getGlobalBounds(); }

        void setPosition(const sf::Vector2f & pos);

        void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

        bool selectNext();
        bool selectPrev();

        void redraw();

        const ListboxIndex getIndexes() const { return m_indexes; }
        void setIndexes(const ListboxIndex & indexes);

      private:
        const item::ItemVec_t & m_items;
        bool m_hasFocus;
        std::size_t m_rowCount;
        const sf::Color m_highlightColor;
        sf::RectangleShape m_bgRectangle;
        ListboxIndex m_indexes;
        std::vector<sf::FloatRect> m_rowRects;
        std::vector<sf::Vertex> m_rowLineVerts;
        std::vector<sf::Text> m_rowTexts;
        sf::RectangleShape m_selectionRectangle;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_GUI_LISTBOX_HPP_INCLUDED
