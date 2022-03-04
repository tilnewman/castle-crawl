// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// map.cpp
//
#include "map.hpp"

#include "board.hpp"
#include "context.hpp"
#include "door-piece.hpp"
#include "media.hpp"
#include "random.hpp"
#include "settings.hpp"
#include "util.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace castlecrawl
{
    void MapVerts::reset()
    {
        floor.clear();
        border.clear();
        wall.clear();
        transition.clear();

        // these reserve values found after trials of the biggest maps
        floor.reserve(4000);
        border.reserve(2000);
        wall.reserve(4000);
        transition.reserve(1000);
    }

    Map::Map()
        : m_isFloorStone(false)
        , m_chars()
        , m_floorChars(false)
        , m_links()

    {}

    Map::Map(
        const util::Random & random,
        const bool isFloorStone,
        const MapChars_t & chars,
        const MapLinks_t & links)
        : m_isFloorStone(isFloorStone)
        , m_chars(chars)
        , m_floorChars()
        , m_links(links)
    {
        updateMapChars(random);
    }

    void Map::updateMapChars(const util::Random & random)
    {
        addWalls();
        addWallCorners();

        m_floorChars = m_chars;
        randomizeFloorTiles(random);
    }

    void Map::load(Context & context, MapVerts & verts)
    {
        resetDoors(context);

        verts.reset();

        makeVerts(context, m_floorChars, verts.floor);
        makeBorderVerts(context, m_floorChars, verts.border);
        makeVerts(context, m_chars, verts.wall);
        makeStoneTransitionVerts(context, verts.transition);
    }

    char Map::getChar(const MapPos_t & pos) const
    {
        if (empty() || !isPosValid(pos))
        {
            return '.';
        }
        else
        {
            return m_chars[static_cast<std::size_t>(pos.y)][static_cast<std::size_t>(pos.x)];
        }
    }

    void Map::setChar(const MapPos_t & pos, const char newChar)
    {
        if (!isPosValid(pos))
        {
            return;
        }

        m_chars[static_cast<std::size_t>(pos.y)][static_cast<std::size_t>(pos.x)] = newChar;
    }

    MapPos_t Map::size() const
    {
        if (m_chars.empty())
        {
            return { 0, 0 };
        }
        else
        {
            return { static_cast<int>(m_chars.front().size()), static_cast<int>(m_chars.size()) };
        }
    }

    void Map::randomizeFloorTiles(const util::Random & random)
    {
        for (std::string & str : m_floorChars)
        {
            for (char & ch : str)
            {
                if ('.' != ch)
                {
                    if (m_isFloorStone)
                    {
                        ch = '6';
                    }
                    else
                    {
                        ch = '0';
                    }

                    ch += random.fromTo<char>(0, 5);
                }
            }
        }
    }

    void Map::addWallCorners()
    {
        if (empty())
        {
            return;
        }

        const MapPos_t mapSize(size());

        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                const char ch{ getChar(x, y) };

                if ((ch != '|') && (ch != '-'))
                {
                    continue;
                }

                const char up{ getChar(x, y - 1) };
                const char down{ getChar(x, y + 1) };
                const char left{ getChar(x - 1, y) };
                const char right{ getChar(x + 1, y) };

                if (ch == '|')
                {
                    if ((left == '-') || (right == '-'))
                    {
                        setChar(x, y, 'B');
                    }

                    if ((down == '|') && ((up == ' ') || (up == '.')))
                    {
                        setChar(x, y, 'B');
                    }

                    if ((up == '|') && ((down == ' ') || (down == '.')))
                    {
                        setChar(x, y, 'B');
                    }
                }
                else //'-'
                {
                    if ((up == '|') || (down == '|'))
                    {
                        setChar(x, y, 'B');
                    }

                    if ((left == '-') && ((right == ' ') || (right == '.')))
                    {
                        setChar(x, y, 'B');
                    }

                    if ((right == '-') && ((left == ' ') || (left == '.')))
                    {
                        setChar(x, y, 'B');
                    }
                }

                if (getChar(x, y) != 'B')
                {
                    continue;
                }

                if ((down == '|') || (down == '-'))
                {
                    if ((right == '|') || (right == '-'))
                    {
                        setChar(x, y, 'C');
                    }
                    else
                    {
                        setChar(x, y, 'T');
                    }
                }
            }
        }
    }

    void Map::addWalls()
    {
        if (empty())
        {
            return;
        }

        auto isNotObs = [](const char ch) { return ((ch != '.') && (ch != '|') && (ch != '-')); };

        const MapPos_t mapSize(size());

        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                const char ch{ getChar(x, y) };

                if (ch != '.')
                {
                    continue;
                }

                // check all four sides
                const char up{ getChar(x, y - 1) };
                const char down{ getChar(x, y + 1) };
                const char left{ getChar(x - 1, y) };
                const char right{ getChar(x + 1, y) };

                if (isNotObs(left) || isNotObs(right))
                {
                    setChar(x, y, '|');
                    continue;
                }
                else if (isNotObs(up) || isNotObs(down))
                {
                    setChar(x, y, '-');
                    continue;
                }

                // check all four corners
                const char tl{ getChar(x - 1, y - 1) };
                const char tr{ getChar(x + 1, y - 1) };
                const char bl{ getChar(x - 1, y + 1) };
                const char br{ getChar(x + 1, y + 1) };

                if (isNotObs(tl) || isNotObs(tr) || isNotObs(bl) || isNotObs(br))
                {
                    setChar(x, y, '|'); // '-' works here too
                    continue;
                }
            }
        }
    }

    void Map::makeVerts(const Context & context, const MapChars_t & mapChars, VertVec_t & verts)
    {
        sf::Sprite tileSprite = context.media.sprite(TileImage::Empty);
        sf::Sprite shadowSprite = context.media.sprite(TileImage::WallHorizShadow);

        const float mapCellDimm{ context.layout.mapCellDimm() };
        const sf::Vector2f boardPos{ util::position(context.layout.boardBounds()) };
        sf::Vector2f pos{ boardPos };

        for (const std::string & mapLine : mapChars)
        {
            char prevMapChar(0);
            for (const char mapChar : mapLine)
            {
                tileSprite = context.media.sprite(mapCharToTileImage(mapChar));
                tileSprite.setPosition(pos);

                util::appendQuadVerts(
                    tileSprite.getGlobalBounds(), tileSprite.getTextureRect(), verts);

                // draw horiz wall shadow accents
                if (('-' == mapChar) && ('-' != prevMapChar))
                {
                    shadowSprite.setPosition(pos);

                    util::appendQuadVerts(
                        shadowSprite.getGlobalBounds(), shadowSprite.getTextureRect(), verts);
                }

                prevMapChar = mapChar;
                pos.x += mapCellDimm;
            }

            pos.x = boardPos.x;
            pos.y += mapCellDimm;
        }
    }

    void Map::makeBorderVerts(
        const Context & context, const MapChars_t & mapChars, VertVec_t & verts)
    {
        sf::Sprite sprite = context.media.sprite(TileImage::Black);
        sprite.setColor(context.config.background_color);
        sprite.scale(1.5f, 1.5f);

        const float mapCellDimm{ context.layout.mapCellDimm() };
        const sf::Vector2f boardPos{ util::position(context.layout.boardBounds()) };

        const float overlapDimm{ mapCellDimm * 0.25f };
        const sf::Vector2f overlap{ overlapDimm, overlapDimm };

        sf::Vector2f pos{ boardPos };

        for (const std::string & mapLine : mapChars)
        {
            for (const char mapChar : mapLine)
            {
                if (mapChar == '.')
                {
                    sprite.setPosition(pos);
                    sprite.move(-overlapDimm, -overlapDimm);

                    util::appendQuadVerts(
                        sprite.getGlobalBounds(), verts, context.config.background_color);
                }

                pos.x += mapCellDimm;
            }

            pos.x = boardPos.x;
            pos.y += mapCellDimm;
        }
    }

    void Map::makeStoneTransitionVerts(const Context & context, VertVec_t & verts)
    {
        if (empty())
        {
            return;
        }

        auto notLiq = [](const char ch) { return ((ch != 'l') && (ch != 'w')); };

        sf::Sprite sprite = context.media.sprite(TileImage::Empty);

        const float mapCellDimm{ context.layout.mapCellDimm() };
        const sf::Vector2f boardPos{ util::position(context.layout.boardBounds()) };
        sf::Vector2f pos{ boardPos };

        const MapPos_t mapSize(size());
        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                const char ch{ getChar(x, y) };

                if (notLiq(ch))
                {
                    pos.x += mapCellDimm;
                    continue;
                }

                // check all four sides
                const char up{ getChar(x, y - 1) };
                const char down{ getChar(x, y + 1) };
                const char left{ getChar(x - 1, y) };
                const char right{ getChar(x + 1, y) };

                if (notLiq(up) && notLiq(left))
                {
                    sprite = context.media.sprite(TileImage::StoneTopLft);
                    sprite.setPosition(pos);
                    util::appendQuadVerts(sprite.getGlobalBounds(), sprite.getTextureRect(), verts);
                }

                if (notLiq(up) && notLiq(right))
                {
                    sprite = context.media.sprite(TileImage::StoneTopRgt);
                    sprite.setPosition(pos);
                    util::appendQuadVerts(sprite.getGlobalBounds(), sprite.getTextureRect(), verts);
                }

                if (notLiq(down) && notLiq(left))
                {
                    sprite = context.media.sprite(TileImage::StoneBotLft);
                    sprite.setPosition(pos);
                    util::appendQuadVerts(sprite.getGlobalBounds(), sprite.getTextureRect(), verts);
                }

                if (notLiq(down) && notLiq(right))
                {
                    sprite = context.media.sprite(TileImage::StoneBotRgt);
                    sprite.setPosition(pos);
                    util::appendQuadVerts(sprite.getGlobalBounds(), sprite.getTextureRect(), verts);
                }

                if (notLiq(up))
                {
                    sprite = context.media.sprite(TileImage::StoneTop);
                    sprite.setPosition(pos);
                    util::appendQuadVerts(sprite.getGlobalBounds(), sprite.getTextureRect(), verts);
                }

                if (notLiq(down))
                {
                    sprite = context.media.sprite(TileImage::StoneBot);
                    sprite.setPosition(pos);
                    util::appendQuadVerts(sprite.getGlobalBounds(), sprite.getTextureRect(), verts);
                }

                if (notLiq(left))
                {
                    sprite = context.media.sprite(TileImage::StoneLft);
                    sprite.setPosition(pos);
                    util::appendQuadVerts(sprite.getGlobalBounds(), sprite.getTextureRect(), verts);
                }

                if (notLiq(right))
                {
                    sprite = context.media.sprite(TileImage::StoneRgt);
                    sprite.setPosition(pos);
                    util::appendQuadVerts(sprite.getGlobalBounds(), sprite.getTextureRect(), verts);
                }

                pos.x += mapCellDimm;
            }

            pos.x = boardPos.x;
            pos.y += mapCellDimm;
        }
    }

    void Map::resetDoors(Context & context)
    {
        context.board.doors.clear();

        if (empty())
        {
            return;
        }

        const MapPos_t mapSize(size());

        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                const MapPos_t mapPos{ x, y };
                const char ch{ getChar(mapPos) };

                if ((ch != 'D') && (ch != 'd'))
                {
                    continue;
                }

                // add piece to board
                DoorPiece door;
                door.reset(context, mapPos, (ch == 'D'));
                context.board.doors.push_back(door);
            }
        }
    }

} // namespace castlecrawl
