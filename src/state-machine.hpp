#ifndef CASTLECRAWL_STATEMACHINE_HPP_INCLUDED
#define CASTLECRAWL_STATEMACHINE_HPP_INCLUDED
//
// state-machine.hpp
//
#include "states.hpp"

#include <optional>
#include <ostream>
#include <string>

namespace castlecrawl
{

    class StateMachine
    {
      public:
        StateMachine();
        virtual ~StateMachine() = default;

        // prevent all copy and assignment
        StateMachine(const StateMachine &) = delete;
        StateMachine(StateMachine &&) = delete;
        //
        StateMachine & operator=(const StateMachine &) = delete;
        StateMachine & operator=(StateMachine &&) = delete;

        State stateEnum() const { return m_stateUPtr->state(); }

        IState & state() { return *m_stateUPtr; }
        const IState & state() const { return *m_stateUPtr; }

        bool isChangePending() const { return m_changePendingOpt.has_value(); }
        StateOpt_t getChangePending() const { return m_changePendingOpt; }
        StateOpt_t getFallback() const { return m_fallbackOpt; }

        void setChangePending(const State state, const StateOpt_t fallback = std::nullopt);

        void setChangePendingToFallback() 
        { 
            if (m_fallbackOpt.has_value())
            {
                m_changePendingOpt = m_fallbackOpt;
            }
        }
        
        void changeIfPending(Context & context);

      private:
        IStateUPtr_t makeState(Context & context, const State state);

      private:
        IStateUPtr_t m_stateUPtr;
        StateOpt_t m_changePendingOpt;
        StateOpt_t m_fallbackOpt;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_STATEMACHINE_HPP_INCLUDED
