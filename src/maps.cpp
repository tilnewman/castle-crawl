// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// maps.hpp
//
#include "maps.hpp"

namespace castlecrawl
{

    void Maps::load(const util::Random & random)
    {
        m_maps.clear();

        // clang-format off
     
        m_maps["level-1-first-room"] = Map {
            random,
            true,
            MapChars_t {
                "...........",
                "...........",
                "...     ...",
                "...     ...",
                "...     ...",
                "...     ...",
                "...     ...",
                "..... .....",
                "..... .....",
                ".....d....."
             },
            MapLinks_t {
                { { 5, 10 }, "level-1-cell-block", { 6, 1 } }
                }
            };

        
        m_maps["level-1-cell-block"] = Map {
            random,
            false,
            MapChars_t {
                "......d...........................",
                "...... ...........................",
                "...... ...........................",
                "......                         bb.",
                "......                          b.",
                "...... ........d...........d......",
                "...... ........ ........... ......",
                "...... ........ ........... ......",
                "....     ....     .     .     ....",
                "....    b....     .     d     ....",
                "....   bb....     .     .     ....",
                ".... ..........d.....d.......d....",
                ".... ........     .     .     ....",
                ".... ........b    d     .     ....",
                ".... ........bb   .     .     ....",
                "....    ...................d......",
                "....... .....     .     .b    ....",
                "....... .....     D     d     ....",
                "....... .....c    .     .     ....",
                "....... ..........................",
                ".......d.........................."
                },
            MapLinks_t {
                { { 6, -1 }, "level-1-first-room",  { 5, 8 } },
                { { 7, 21 }, "level-1-main-hall",  { 16, 1 } }
                }
            };

        
        m_maps["level-1-main-hall"] = Map {
            random,
            false,
            MapChars_t {
                "................d.................",
                "................ .................",
                "................ .................",
                ".............       ..............",
                ".....    ....       ......       d",
                ".....       D       ......b bbb...",
                ".....c   ....       ......   bb...",
                ".............       ......    b...",
                ".............       ......     ...",
                ".............       d          ...",
                ".............       ..............",
                "..          d       ..............",
                "..b      ....       ..............",
                "..bb     ....       ..............",
                "..bbb    ....       ......b    b..",
                "..b      ....       ......      ..",
                "..          d       D           ..",
                "..       ....       ......      ..",
                "..     bb....       ......b    b..",
                ".............       ..............",
                "................ .................",
                "................ .................",
                "................s................."
                },
            MapLinks_t {
                { { 16, -1 }, "level-1-cell-block",  { 7, 19 } },
                { { 16, 23 }, "level-1-boiler-room", { 2,  0 } },
                { { 34, 4 }, "level-1-hidden-passage", { 1,  2 } }
                }
            };

        m_maps["level-1-boiler-room"] = Map {
            random,
            true,
            MapChars_t {
                "..S..............................",
                ".. ..............................",
                ".. ....ll  llllllll..............",
                ".. ....  l  lllllll..............",
                ".. ....b    ll  bbb.  bb.........",
                ".. ....      l   bb.   b.........",
                ".. .......        b.    .........",
                "..       .         .    .........",
                "........ .......D...    .........",
                "........ .              .........",
                "........d.              .........",
                "....                    .........",
                "....            .................",
                "....            . bbwwwwwww......",
                "....            D   www..........",
                "....            .   www..........",
                "............ ....................",
                ".......l  b     .................",
                ".......bb      b.................",
                ".......bbbbllbbb.................",
                ".................................",
                "................................."
                },
            MapLinks_t {
                { { 2,  -1 }, "level-1-main-hall", { 16, 22 } }
                }
            };
        
        m_maps["level-1-hidden-passage"] = Map {
            random,
            false,
            MapChars_t {
                "...................",
                "...................",
                "d            ......",
                "............ ......",
                "............ ......",
                "............d......",
                ".........       ...",
                ".........       ...",
                ".........       ...",
                ".........       ...",
                "............d......",
                "............ ......",
                "............ ......",
                "............ ......",
                "............ ......",
                "............ ......",
                "............       ",
                "...................",
                "...................",
                "...................",
                "..................."
                },
            MapLinks_t {
                { { -1, 2 }, "level-1-main-hall",  { 32, 4 } },
                { { 19, 16 }, "level-1-coffin-room", { 0,  9 } }
                }
            };

        m_maps["level-1-coffin-room"] = Map {
            random,
            true,
            MapChars_t {
                ".................................",
                ".................................",
                "...................    cc........",
                "........ccc........     c........",
                "........   .......... ...........",
                "....c      .......... ...........",
                "....... ............. ...........",
                "....... ............. ...........",
                ".......D............. ...........",
                "        D             ...........",
                ".......D.........................",
                "....... .........................",
                "....... .........................",
                "....... .........................",
                "....... .........................",
                "..           ....................",
                "..c          ....................",
                "..cc         ....................",
                "..ccc c    cc....................",
                ".................................",
                "................................."
                },
            MapLinks_t {
                { { -1, 9 }, "level-1-hidden-passage", { 18, 16 } }
                }
            };

        // clang-format on
    }

} // namespace castlecrawl
