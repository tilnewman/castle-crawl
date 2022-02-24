#ifndef CASTLECRAWLMAPPER_STATES_HPP_INCLUDED
#define CASTLECRAWLMAPPER_STATES_HPP_INCLUDED
//
// states.hpp
//
#include <optional>
#include <ostream>
#include <string>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace mapper
{
    struct Context;

    enum class State
    {
        Setup = 0,
        Edit,
        Popup,
        Teardown,
    };

    using StateOpt_t = std::optional<State>;

    struct IState
    {
        virtual ~IState() = default;

        virtual State which() const = 0;
        virtual void update(Context &, const float elapsedSec) = 0;
        virtual void handleEvent(Context & context, const sf::Event & event) = 0;
        virtual void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const = 0;
        virtual void onEnter(Context &) = 0;
        virtual void onExit(Context &) = 0;
    };

    using IStateUPtr_t = std::unique_ptr<IState>;

    class StateBase : public IState
    {
      protected:
        StateBase(const State state);

      public:
        virtual ~StateBase() override = default;

        // prevent all copy and assignment
        StateBase(const StateBase &) = delete;
        StateBase(StateBase &&) = delete;
        //
        StateBase & operator=(const StateBase &) = delete;
        StateBase & operator=(StateBase &&) = delete;

        State which() const final { return m_state; }

        void update(Context &, const float) override {}
        void handleEvent(Context &, const sf::Event &) override {}
        void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const override {}
        void onEnter(Context &) override {}
        void onExit(Context &) override {}

      protected:
        State m_state;
    };

    class StateSetup : public StateBase
    {
      public:
        StateSetup()
            : StateBase(State::Setup)
        {}
    };

    class StateTeardown : public StateBase
    {
      public:
        StateTeardown(Context &)
            : StateBase(State::Teardown)
        {}
    };

} // namespace mapper

#endif // CASTLECRAWLMAPPER_STATES_HPP_INCLUDED
