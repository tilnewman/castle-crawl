#ifndef CASTLECRAWL_TILEIMAGE_HPP_INCLUDED
#define CASTLECRAWL_TILEIMAGE_HPP_INCLUDED
//
// tile-image.hpp
//
#include <cstddef>

#include <SFML/Graphics/Rect.hpp>

namespace castlecrawl
{
    // used to index so keep unsigned
    enum class TileImage : std::size_t
    {
        Empty = 0,
        Wood1,
        Wood2,
        Wood3,
        Wood4,
        Wood5,
        Wood6,
        Stone1,
        Stone2,
        Stone3,
        Stone4,
        Stone5,
        Stone6,
        Black,
        Lava,
        Water,
        WallBlock,
        WallTopLeft,
        WallTop,
        WallHoriz,
        WallHorizShadow,
        WallVert,
        Player,
        Barrel,
        Door,
        DoorLocked,
        Coffin,
        Chest,
        StairUp,
        StairDown,
        StoneTopLft,
        StoneTop,
        StoneTopRgt,
        StoneLft,
        StoneRgt,
        StoneBotLft,
        StoneBot,
        StoneBotRgt,
        Count
    };

    inline constexpr char tileImageChar(const TileImage tileImage) noexcept
    {
        // clang-format off
        switch (tileImage)
        {
            case TileImage::Wood1:          { return '0'; }
            case TileImage::Wood2:          { return '1'; }
            case TileImage::Wood3:          { return '2'; }
            case TileImage::Wood4:          { return '3'; }
            case TileImage::Wood5:          { return '4'; }
            case TileImage::Wood6:          { return '5'; }
            case TileImage::Stone1:         { return '6'; }
            case TileImage::Stone2:         { return '7'; }
            case TileImage::Stone3:         { return '8'; }
            case TileImage::Stone4:         { return '9'; }
            case TileImage::Stone5:         { return ':'; }
            case TileImage::Stone6:         { return ';'; }
            case TileImage::Lava:           { return 'l'; }
            case TileImage::Water:          { return 'w'; }
            case TileImage::WallBlock:      { return 'B'; }
            case TileImage::WallTopLeft:    { return 'C'; }
            case TileImage::WallTop:        { return 'T'; }
            case TileImage::WallHoriz:      { return '-'; }
            case TileImage::WallVert:       { return '|'; }
            case TileImage::Barrel:         { return 'b'; }
            case TileImage::Door:           { return 'd'; }
            case TileImage::DoorLocked:     { return 'D'; }
            case TileImage::Coffin:         { return 'k'; }
            case TileImage::Chest:          { return 'c'; }
            case TileImage::StairUp:        { return 'S'; }
            case TileImage::StairDown:      { return 's'; }
            case TileImage::Player:         { return 'p'; }
            case TileImage::Empty:          { return ' '; }
            case TileImage::WallHorizShadow:
            case TileImage::Black:
            case TileImage::StoneTopLft:
            case TileImage::StoneTop:
            case TileImage::StoneTopRgt:
            case TileImage::StoneLft:
            case TileImage::StoneRgt:
            case TileImage::StoneBotLft:
            case TileImage::StoneBot:
            case TileImage::StoneBotRgt:
            case TileImage::Count:
            default:                        { return '.'; }
        }
        // clang-format on
    }

    inline constexpr TileImage tileImage(const char mapChar) noexcept
    {
        switch (mapChar)
        {
            case 'B': return TileImage::WallBlock;
            case 'C': return TileImage::WallTopLeft;
            case 'T': return TileImage::WallTop;
            case '-': return TileImage::WallHoriz;
            case '|': return TileImage::WallVert;
            case 'p': return TileImage::Player;
            case 'b': return TileImage::Barrel;
            case 'D': return TileImage::DoorLocked;
            case 'd': return TileImage::Door;
            case 'k': return TileImage::Coffin;
            case 'c': return TileImage::Chest;
            case 'S': return TileImage::StairUp;
            case 's': return TileImage::StairDown;
            case '0': return TileImage::Wood1;
            case '1': return TileImage::Wood2;
            case '2': return TileImage::Wood3;
            case '3': return TileImage::Wood4;
            case '4': return TileImage::Wood5;
            case '5': return TileImage::Wood6;
            case '6': return TileImage::Stone1;
            case '7': return TileImage::Stone2;
            case '8': return TileImage::Stone3;
            case '9': return TileImage::Stone4;
            case ':': return TileImage::Stone5;
            case ';': return TileImage::Stone6;
            case 'l': return TileImage::Lava;
            case 'w': return TileImage::Water;
            default: return TileImage::Empty;
        }
    }

    inline sf::IntRect tileImageToTileRect(const TileImage image) noexcept
    {
        // clang-format off
        switch (image)
        {
            case TileImage::WallBlock:       return sf::IntRect( 64,32,32,32);
            case TileImage::WallTopLeft:     return sf::IntRect(  0, 0,32,32);
            case TileImage::WallTop:         return sf::IntRect( 64, 0,32,32);
            case TileImage::WallHoriz:       return sf::IntRect( 32, 0,32,32);
            case TileImage::WallHorizShadow: return sf::IntRect( 32,32,32,32);
            case TileImage::WallVert:        return sf::IntRect(  0,32,32,32);
            case TileImage::Player:          return sf::IntRect( 96,32,32,32);
            case TileImage::Barrel:          return sf::IntRect( 96, 0,32,32);
            case TileImage::Door:            return sf::IntRect( 96,96,32,32);
            case TileImage::DoorLocked:      return sf::IntRect( 96,96,32,32);
            case TileImage::Chest:           return sf::IntRect( 96,64,32,32);
            case TileImage::Coffin:          return sf::IntRect(160,64,32,32);
            case TileImage::StairUp:         return sf::IntRect(128, 0,32,32);
            case TileImage::StairDown:       return sf::IntRect(128,32,32,32);
            //
            case TileImage::Wood1:           return sf::IntRect( 0,64,32,32);
            case TileImage::Wood2:           return sf::IntRect(32,64,32,32);
            case TileImage::Wood3:           return sf::IntRect(64,64,32,32);
            case TileImage::Wood4:           return sf::IntRect( 0,96,32,32);
            case TileImage::Wood5:           return sf::IntRect(32,96,32,32);
            case TileImage::Wood6:           return sf::IntRect(64,96,32,32);
            //
            case TileImage::Stone1:          return sf::IntRect( 0,128,32,32);
            case TileImage::Stone2:          return sf::IntRect(32,128,32,32);
            case TileImage::Stone3:          return sf::IntRect(64,128,32,32);
            case TileImage::Stone4:          return sf::IntRect( 0,160,32,32);
            case TileImage::Stone5:          return sf::IntRect(32,160,32,32);
            case TileImage::Stone6:          return sf::IntRect(64,160,32,32);
            //
            case TileImage::StoneTopLft:     return sf::IntRect( 96,128,32,32);
            case TileImage::StoneTop:        return sf::IntRect(128,128,32,32);
            case TileImage::StoneTopRgt:     return sf::IntRect(160,128,32,32);
            case TileImage::StoneLft:        return sf::IntRect( 96,160,32,32);
            case TileImage::StoneRgt:        return sf::IntRect(160,160,32,32);
            case TileImage::StoneBotLft:     return sf::IntRect( 96,192,32,32);
            case TileImage::StoneBot:        return sf::IntRect(128,192,32,32);
            case TileImage::StoneBotRgt:     return sf::IntRect(160,192,32,32);
            //
            case TileImage::Black:           return sf::IntRect( 0,192,32,32);
            case TileImage::Lava:            return sf::IntRect(32,192,32,32);
            case TileImage::Water:           return sf::IntRect(64,192,32,32);
            //
            case TileImage::Empty:                 
            case TileImage::Count:
            default:                         return sf::IntRect(0,0,0,0);
        }
        // clang-format on
    }

} // namespace castlecrawl
#endif // CASTLECRAWL_TILEIMAGE_HPP_INCLUDED
