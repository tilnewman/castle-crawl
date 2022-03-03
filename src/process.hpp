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

	struct Process
    {
        Action action = Action::None;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_PROCESS_HPP_INCLUDED
