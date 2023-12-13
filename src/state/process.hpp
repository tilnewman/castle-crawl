#ifndef CASTLECRAWL_PROCESS_HPP_INCLUDED
#define CASTLECRAWL_PROCESS_HPP_INCLUDED
//
// process.hpp
//

namespace castlecrawl
{

    enum class Action
    {
        None,
        Fight
    };

    inline constexpr std::string_view toString(const Action action) noexcept
    {
        // clang-format off
        switch(action)
        {
            case Action::None:  { return ""; }
            case Action::Fight: { return "Fight"; }
            default:            { return "Action::Invalid"; }
        }
        // clang-format on
    }

    struct Process
    {
        Action action = Action::None;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_PROCESS_HPP_INCLUDED
