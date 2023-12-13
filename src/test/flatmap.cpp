#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "misc/flat-map.hpp"

#include <string>

TEST_CASE( "Default empty FlatMap", "[FlatMap]" ) 
{
    util::FlatMap<std::string, int> map;

    REQUIRE( map.empty() == true );
    REQUIRE( map.size() == 0 );
}
