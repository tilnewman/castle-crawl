// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-machine.cpp
//
#include "state-machine.hpp"

#include "context.hpp"
#include "state-edit.hpp"
#include "state-popup.hpp"

#include <iostream>

namespace mapper
{

    StateMachine::StateMachine()
        : m_stateUPtr(std::make_unique<StateSetup>())
        , m_changePendingOpt()
    {}

    void StateMachine::changeIfPending(Context & context)
    {
        if (!m_changePendingOpt)
        {
            return;
        }

        m_stateUPtr->onExit(context);

        m_stateUPtr.reset();
        m_stateUPtr = makeState(context, m_changePendingOpt.value());
        m_changePendingOpt.reset();

        m_stateUPtr->onEnter(context);
    }

    IStateUPtr_t StateMachine::makeState(Context & context, const State state)
    {
        switch (state)
        {
            // clang-format off
            case State::Setup:   { return std::make_unique<StateSetup>();           }
            case State::Edit:    { return std::make_unique<StateEdit>(context);     }
            case State::Popup:   { return std::make_unique<StatePopup>(context);    }
            case State::Teardown:{ return std::make_unique<StateTeardown>(context); }
                // clang-format on
            default: {
                std::cerr << "ERROR:  StateMachine::makeState(" << static_cast<int>(state)
                          << ") not handled in switch.  Bail." << std::endl;

                return std::make_unique<StateTeardown>(context);
            }
        };
    }

} // namespace mapper
