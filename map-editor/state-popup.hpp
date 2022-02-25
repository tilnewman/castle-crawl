#ifndef CASTLECRAWLMAPPER_STATEPOPUP_HPP_INCLUDED
#define CASTLECRAWLMAPPER_STATEPOPUP_HPP_INCLUDED
//
// state-popup.hpp
//
#include "state-edit.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace mapper
{
    struct Context;

    //
    class StatePopup : public StateEdit
    {
      public:
        StatePopup(Context & context);

        void onEnter(Context & context) override;
        void onExit(Context & context) override;
        void handleEvent(Context &, const sf::Event &) override;
        void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const override;
    };

} // namespace mapper

#endif // CASTLECRAWLMAPPER_STATEPOPUP_HPP_INCLUDED
