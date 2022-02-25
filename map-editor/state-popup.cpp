// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-popup.cpp
//
#include "state-popup.hpp"

#include "context.hpp"
#include "popup-manager.hpp"
#include "sound-player.hpp"
#include "state-machine.hpp"

#include <SFML/Graphics.hpp>

namespace mapper
{

    StatePopup::StatePopup(Context & context)
        : StateEdit(context)
    {}

    void StatePopup::onEnter(Context & context) { context.audio.play("thock-1"); }
    void StatePopup::onExit(Context & context) { context.audio.play("thock-3"); }

    void StatePopup::handleEvent(Context & context, const sf::Event & event)
    {
        if ((sf::Event::MouseButtonPressed == event.type) || (sf::Event::KeyPressed == event.type))
        {
            context.state.setChangePending(State::Edit);
            return;
        }
    }

    void StatePopup::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        StateEdit::draw(context, target, states);
        target.draw(context.popup);
    }

} // namespace mapper
