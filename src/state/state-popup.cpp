// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-popup.cpp
//
#include "state/state-popup.hpp"

#include "display/popup-manager.hpp"
#include "misc/check-macros.hpp"
#include "misc/context.hpp"
#include "state/state-machine.hpp"

namespace castlecrawl
{
    StatePopup::StatePopup(Context & context)
        : StatePlay(context)
    {}

    void StatePopup::onEnter(Context &) {}

    void StatePopup::handleEvent(Context & context, const sf::Event & event)
    {
        if ((sf::Event::KeyPressed == event.type) || (sf::Event::MouseButtonPressed == event.type))
        {
            context.state.setChangePendingToFallback();
            return;
        }
    }

    void StatePopup::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        StatePlay::draw(context, target, states);
        target.draw(context.popup);
    }

} // namespace castlecrawl
