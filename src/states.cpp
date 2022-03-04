// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// states.cpp
//
#include "states.hpp"

#include "context.hpp"
#include "settings.hpp"
#include "state-machine.hpp"

#include <ostream>

namespace castlecrawl
{

    StateBase::StateBase(const State state)
        : m_state(state)
    {}

    void StateQuit::onEnter(Context & context) { context.game.endGame(false); }

    std::ostream & operator<<(std::ostream & os, const State state)
    {
        os << toString(state);
        return os;
    }

} // namespace castlecrawl
