// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-machine.cpp
//
#include "state-machine.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "state-direction.hpp"
#include "state-edit.hpp"
#include "state-inventory.hpp"
#include "state-pause.hpp"
#include "state-play.hpp"
#include "state-popup.hpp"
#include "state-splash.hpp"
#include "state-treasure.hpp"

#include <iostream>

namespace castlecrawl
{

    StateMachine::StateMachine()
        : m_stateUPtr()
        , m_changePendingOpt(State::Init)
        , m_fallbackOpt(std::nullopt)
    {
        m_stateUPtr = std::make_unique<StateInit>();
        m_changePendingOpt = m_stateUPtr->state();
    }

    void StateMachine::changeIfPending(Context & context)
    {
        if (!m_changePendingOpt)
        {
            return;
        }

        m_stateUPtr->onExit(context);

        m_stateUPtr.reset();
        m_stateUPtr = makeState(context, m_changePendingOpt.value());
        m_changePendingOpt = std::nullopt;

        m_stateUPtr->onEnter(context);
    }

    IStateUPtr_t StateMachine::makeState(Context & context, const State state)
    {
        switch (state)
        {
            // clang-format off
            case State::Init:     { return std::make_unique<StateInit>();             }
            case State::Load:     { return std::make_unique<StateLoad>();             }
            case State::Splash:   { return std::make_unique<StateSplash>();           }
            case State::Play:     { return std::make_unique<StatePlay>(context);      }
            case State::Pause:    { return std::make_unique<StatePause>(context);     }
            case State::Popup:    { return std::make_unique<StatePopup>(context);     }
            case State::Quit:     { return std::make_unique<StateQuit>(context);      }
            case State::Direction:{ return std::make_unique<StateDirection>(context); }
            case State::Inventory:{ return std::make_unique<StateInventory>(context); }
            case State::Treasure: { return std::make_unique<StateTreasure>(context);  }
            case State::Edit:     { return std::make_unique<StateEdit>(context);      }
            // clang-format on
            default: {
                std::cerr << "ERROR:  StateMachine::makeState(\"" << state
                          << "\") not handled in switch.  Bail." << std::endl;

                return std::make_unique<StateQuit>(context);
            }
        };
    }

    void StateMachine::setChangePending(const State state, const StateOpt_t & fallback)
    {
        m_changePendingOpt = state;
        m_fallbackOpt = fallback;

        if (requiresFallback(state))
        {
            M_CHECK(
                (m_fallbackOpt.has_value()),
                "Error:  Transitioned to state " << toString(state) << " without fallback!");
        }
    }

} // namespace castlecrawl
