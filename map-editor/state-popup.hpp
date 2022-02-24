#ifndef CASTLECRAWL_STATEPOPUP_HPP_INCLUDED
#define CASTLECRAWL_STATEPOPUP_HPP_INCLUDED
//
// state-popup.hpp
//
#include "state-edit.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace castlecrawl
{
    struct Context;

    //
    class StatePopup : public StateEdit
    {
      public:
        StatePopup(Context & context);

        void handleEvent(Context &, const sf::Event &) override;
        void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const override;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_STATEPOPUP_HPP_INCLUDED
