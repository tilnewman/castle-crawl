// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// maps.hpp
//
#include "maps.hpp"

#include "board.hpp"
#include "check-macros.hpp"
#include "context.hpp"
#include "media.hpp"
#include "settings.hpp"
#include "util.hpp"

#include <fstream>

#include <SFML/Graphics/RenderTarget.hpp>

namespace castlecrawl
{

    Maps::Maps()
        : m_maps()
        , m_currentMapName()
        , m_invalidMap()
        , m_currentMapPtr(&m_invalidMap)
    {}

    void Maps::loadAll(const util::Random & random)
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
                { { 5, 10 }, "level-1-cell-block", { 5, 1 } }
                }
            };

        
        m_maps["level-1-cell-block"] = Map {
            random,
            false,
            MapChars_t {
                ".....d............................",
                "..... ............................",
                "..... ............................",
                ".....                         bb..",
                ".....                          b..",
                "..... ........d...........d.......",
                "..... ........ ........... .......",
                "..... ........ ........... .......",
                "...     ....     .     .     .....",
                "...    b....     .     d     .....",
                "...   bb....     .     .     .....",
                "... ..........d.....d.......d.....",
                "... ........     .     .     .....",
                "... ........b    d     .     .....",
                "... ........bb   .     .     .....",
                "...    ...................d.......",
                "...... .....     .     .b    .....",
                "...... .....     D     d     .....",
                "...... .....c    .     .     .....",
                "...... ...........................",
                "......d..........................."
                },
            MapLinks_t {
                { { 5, -1 }, "level-1-first-room",  { 5, 8 } },
                { { 6, 21 }, "level-1-main-hall",  { 16, 1 } }
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
                { { 16, -1 }, "level-1-cell-block",  { 6, 19 } },
                { { 16, 23 }, "level-1-boiler-room", { 2,  0 } },
                { { 34, 4 }, "level-1-hidden-passage", { 1,  2 } }
                }
            };

        m_maps["level-1-boiler-room"] = Map {
            random,
            true,
            MapChars_t {
                "..S..........................",
                ".. ..........................",
                ".. ....ll  llllllll..........",
                ".. ....  l  lllllll..........",
                ".. ....b    ll  bbb.  bb.....",
                ".. ....      l   bb.   b.....",
                ".. .......        b.    .....",
                "..       .         .    .....",
                "........ .......D...    .....",
                "........ .              .....",
                "........d.              .....",
                "....                    .....",
                "....            .............",
                "....            . bbwwwwwww..",
                "....            d   www......",
                "....            .   www......",
                "............ ................",
                ".......l  b     .............",
                ".......bb      b.............",
                ".......bbbbllbbb.............",
                ".............................",
                "............................."
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
                "...................    kk........",
                "........kkk........     k........",
                "........   .......... ...........",
                "....k      .......... ...........",
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
                "..k          ....................",
                "..kk         ....................",
                "..kkk k    kk....................",
                ".................................",
                "................................."
                },
            MapLinks_t {
                { { -1, 9 }, "level-1-hidden-passage", { 18, 16 } }
                }
            };
        // clang-format on

        // this sort is not required but helps performance
        m_maps.sortAndUnique();
    }

    void Maps::switchTo(Context & context, const MapLink & link)
    {
        const std::string fromMapName = m_currentMapName;
        m_currentMapName = link.to_name;

        const auto iter = m_maps.find(m_currentMapName);

        M_CHECK(
            (!iter->second.empty()),
            "Map is empty!  from=\"" << fromMapName << "\" to " << link.to_pos << " in \""
                                     << m_currentMapName << "\"");

        m_currentMapPtr = &iter->second;

        context.layout.calcBoardValues(m_currentMapPtr->size());
        m_currentMapPtr->load(context, m_verts, link.to_pos);
    }

    void Maps::reloadAfterChange(Context & context)
    {
        m_currentMapPtr->load(context, m_verts, context.board.player().position());
    }

    void Maps::drawCurrent(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        states.texture = &context.media.tileTexture();

        if (!m_verts.floor.empty())
        {
            target.draw(&m_verts.floor[0], m_verts.floor.size(), sf::Quads, states);
        }

        if (!m_verts.border.empty())
        {
            // do not use states because these verts have no texture
            target.draw(&m_verts.border[0], m_verts.border.size(), sf::Quads);
        }

        if (!m_verts.transition.empty())
        {
            target.draw(&m_verts.transition[0], m_verts.transition.size(), sf::Quads, states);
        }
    }

    void Maps::dumpAllToFile() const
    {
        std::ofstream fileStream("converted-maps.txt", std::ios_base::trunc);

        for (const auto & pair : m_maps)
        {
            const auto & strings = pair.second.strings();

            for (const std::string & row : strings)
            {
                fileStream << row << '\n';
            }

            fileStream << "\n\n";
        }
    }

} // namespace castlecrawl
