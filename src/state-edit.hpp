#ifndef CASTLECRAWL_STATE_EDIT_HPP_INCLUDED
#define CASTLECRAWL_STATE_EDIT_HPP_INCLUDED
//
// state-edit.hpp
//
#include "editor.hpp"
#include "states.hpp"

#include <string>

#include <SFML/Graphics/RectangleShape.hpp>

namespace castlecrawl
{
    struct Context;

    class StateEdit : public StateBase
    {
      public:
        StateEdit(Context & context);

        void onEnter(Context & context) override;
        void handleEvent(Context & context, const sf::Event & event) override;
        void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const override;

      private:
        Editor m_editor;
        sf::RectangleShape m_windowOutline;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_STATE_EDIT_HPP_INCLUDED
