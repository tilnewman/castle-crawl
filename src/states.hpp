#ifndef CASTLECRAWL_STATES_HPP_INCLUDED
#define CASTLECRAWL_STATES_HPP_INCLUDED
//
// states.hpp
//
#include <iosfwd>
#include <optional>
#include <string>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace sf
{
    class RenderTarget;
    class Event;
} // namespace sf
namespace castlecrawl
{
    struct Context;

    enum class State : std::size_t
    {
        Init = 0,
        Load,
        Splash,
        Play,
        Pause,
        Popup,
        Direction,
        Inventory,
        Quit,
    };

    using StateOpt_t = std::optional<State>;

    inline constexpr std::string_view toString(const State state) noexcept
    {
        switch (state)
        {
            case State::Init: return "Init";
            case State::Load: return "Load";
            case State::Splash: return "Splash";
            case State::Popup: return "Popup";
            case State::Play: return "Play";
            case State::Pause: return "Pause";
            case State::Quit: return "Quit";
            case State::Direction: return "Direction";
            case State::Inventory: return "Inventory";
            default: return "State::Invalid";
        }
    }

    inline constexpr bool requiresFallback(const State state) noexcept
    {
        return ((state == State::Popup) || (state == State::Direction) || (state == State::Pause));
    }

    std::ostream & operator<<(std::ostream & os, const State state);

    //

    struct IState
    {
        virtual ~IState() = default;

        virtual State state() const = 0;
        virtual void update(Context &, const float elapsedSec) = 0;
        virtual void handleEvent(Context & context, const sf::Event & event) = 0;
        virtual void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const = 0;
        virtual void onEnter(Context &) = 0;
        virtual void onExit(Context &) = 0;
    };

    using IStateUPtr_t = std::unique_ptr<IState>;

    //

    class StateBase : public IState
    {
      protected:
        explicit StateBase(const State state);

      public:
        virtual ~StateBase() override = default;

        // prevent all copy and assignment
        StateBase(const StateBase &) = delete;
        StateBase(StateBase &&) = delete;
        //
        StateBase & operator=(const StateBase &) = delete;
        StateBase & operator=(StateBase &&) = delete;

        State state() const final { return m_state; }

        void update(Context &, const float) override {}
        void handleEvent(Context &, const sf::Event &) override {}
        void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const override {}
        void onEnter(Context &) override {}
        void onExit(Context &) override {}

      protected:
        State m_state;
    };

    //

    class StateInit : public StateBase
    {
      public:
        StateInit()
            : StateBase(State::Init)
        {}
    };

    class StateLoad : public StateBase
    {
      public:
        StateLoad()
            : StateBase(State::Load)
        {}

        void onEnter(Context & context) override;
    };

    class StateQuit : public StateBase
    {
      public:
        explicit StateQuit(Context &)
            : StateBase(State::Quit)
        {}

        void onEnter(Context & context) override;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_STATES_HPP_INCLUDED
