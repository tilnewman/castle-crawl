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
        Dirt1,
        Dirt2,
        Dirt3,
        Dirt4,
        Dirt5,
        Plant1,
        Plant2,
        Plant3,
        Plant4,
        Lava,
        Water,
        Slime,
        WallBlock,
        WallTopLeft,
        WallTop,
        WallHoriz,
        WallHorizShadow,
        WallVert,
        Rock,
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
        SnakeBag,
        Snake,
        SpiderWeb,
        Spider,
        GoblinPot,
        Goblin,
        BirdMask,
        Bat,
        SkeletonGrave,
        Skeleton,
        DemonDoor,
        Demon,
        DragonBreath,
        Dragon,
        Count
    };

    // only bother to implement the obstacles and Empty
    inline constexpr char tileImageChar(const TileImage tileImage) noexcept
    {
        // clang-format off
        switch (tileImage)
        {
            case TileImage::Lava:           { return 'l'; }
            case TileImage::Water:          { return 'w'; }
            case TileImage::Slime:          { return 'a'; }
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
            case TileImage::Plant1:         { return '@'; }
            case TileImage::Plant2:         { return '#'; }
            case TileImage::Plant3:         { return '$'; }
            case TileImage::Plant4:         { return '%'; }
            case TileImage::Rock:           { return 'r'; }
            case TileImage::Empty:          { return ' '; }
            case TileImage::SnakeBag:       { return '\x80'; }
            case TileImage::Snake:          { return '\x81'; }
            case TileImage::SpiderWeb:      { return '\x82'; }
            case TileImage::Spider:         { return '\x83'; }
            case TileImage::GoblinPot:      { return '\x84'; }
            case TileImage::Goblin:         { return '\x85'; }
            case TileImage::BirdMask:       { return '\x86'; }
            case TileImage::Bat:            { return '\x87'; }
            case TileImage::SkeletonGrave:  { return '\x88'; }
            case TileImage::Skeleton:       { return '\x89'; }
            case TileImage::DemonDoor:      { return '\x8A'; }
            case TileImage::Demon:          { return '\x8B'; }
            case TileImage::DragonBreath:   { return '\x8C'; }
            case TileImage::Dragon:         { return '\x8D'; }
            case TileImage::Dirt1:
            case TileImage::Dirt2:
            case TileImage::Dirt3:
            case TileImage::Dirt4:
            case TileImage::Dirt5:
            case TileImage::Wood1:
            case TileImage::Wood2:
            case TileImage::Wood3:
            case TileImage::Wood4:
            case TileImage::Wood5:
            case TileImage::Wood6:
            case TileImage::Stone1:
            case TileImage::Stone2:
            case TileImage::Stone3:
            case TileImage::Stone4:
            case TileImage::Stone5:
            case TileImage::Stone6:
            case TileImage::WallHorizShadow:
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
            case 'r': return TileImage::Rock;
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
            case 'a': return TileImage::Slime;
            case '[': return TileImage::Dirt1;
            case ']': return TileImage::Dirt2;
            case '{': return TileImage::Dirt3;
            case '}': return TileImage::Dirt4;
            case '<': return TileImage::Dirt5;
            case '@': return TileImage::Plant1;
            case '#': return TileImage::Plant2;
            case '$': return TileImage::Plant3;
            case '%': return TileImage::Plant4;
            case '\x80': return TileImage::SnakeBag;
            case '\x81': return TileImage::Snake;
            case '\x82': return TileImage::SpiderWeb;
            case '\x83': return TileImage::Spider;
            case '\x84': return TileImage::GoblinPot;
            case '\x85': return TileImage::Goblin;
            case '\x86': return TileImage::BirdMask;
            case '\x87': return TileImage::Bat;
            case '\x88': return TileImage::SkeletonGrave;
            case '\x89': return TileImage::Skeleton;
            case '\x8A': return TileImage::DemonDoor;
            case '\x8B': return TileImage::Demon;
            case '\x8C': return TileImage::DragonBreath;
            case '\x8D': return TileImage::Dragon;
            default: return TileImage::Empty;
        }
    }

    inline sf::IntRect tileImageToTileRect(const TileImage image) noexcept
    {
        // clang-format off
        switch (image)
        {
            case TileImage::WallBlock:       return {  64,  32, 32, 32 };
            case TileImage::WallTopLeft:     return {   0,   0, 32, 32 };
            case TileImage::WallTop:         return {  64,   0, 32, 32 };
            case TileImage::WallHoriz:       return {  32,   0, 32, 32 };
            case TileImage::WallHorizShadow: return {  32,  32, 32, 32 };
            case TileImage::WallVert:        return {   0,  32, 32, 32 };
            case TileImage::Player:          return {  96,  32, 32, 32 };
            case TileImage::Barrel:          return {  96,   0, 32, 32 };
            case TileImage::Door:            return {  96,  96, 32, 32 };
            case TileImage::DoorLocked:      return {  96,  96, 32, 32 };
            case TileImage::Chest:           return {  96,  64, 32, 32 };
            case TileImage::Coffin:          return { 160,  64, 32, 32 };
            case TileImage::StairUp:         return { 128,   0, 32, 32 };
            case TileImage::StairDown:       return { 128,  32, 32, 32 };
            case TileImage::Wood1:           return {   0,  64, 32, 32 };
            case TileImage::Wood2:           return {  32,  64, 32, 32 };
            case TileImage::Wood3:           return {  64,  64, 32, 32 };
            case TileImage::Wood4:           return {   0,  96, 32, 32 };
            case TileImage::Wood5:           return {  32,  96, 32, 32 };
            case TileImage::Wood6:           return {  64,  96, 32, 32 };
            case TileImage::Stone1:          return {   0, 128, 32, 32 };
            case TileImage::Stone2:          return {  32, 128, 32, 32 };
            case TileImage::Stone3:          return {  64, 128, 32, 32 };
            case TileImage::Stone4:          return {   0, 160, 32, 32 };
            case TileImage::Stone5:          return {  32, 160, 32, 32 };
            case TileImage::Stone6:          return {  64, 160, 32, 32 };
            case TileImage::StoneTopLft:     return {  96, 128, 32, 32 };
            case TileImage::StoneTop:        return { 128, 128, 32, 32 };
            case TileImage::StoneTopRgt:     return { 160, 128, 32, 32 };
            case TileImage::StoneLft:        return {  96, 160, 32, 32 };
            case TileImage::StoneRgt:        return { 160, 160, 32, 32 };
            case TileImage::StoneBotLft:     return {  96, 192, 32, 32 };
            case TileImage::StoneBot:        return { 128, 192, 32, 32 };
            case TileImage::StoneBotRgt:     return { 160, 192, 32, 32 };
            case TileImage::Rock:            return {   0, 192, 32, 32 };
            case TileImage::Lava:            return {  32, 192, 32, 32 };
            case TileImage::Water:           return {  64, 192, 32, 32 };
            case TileImage::Slime:           return { 128, 160, 32, 32 };
            case TileImage::Dirt1:           return { 160,   0, 32, 32 };
            case TileImage::Dirt2:           return { 192,   0, 32, 32 };
            case TileImage::Dirt3:           return { 160,  32, 32, 32 };
            case TileImage::Dirt4:           return { 192,  32, 32, 32 };
            case TileImage::Dirt5:           return { 224,  32, 32, 32 };       
            case TileImage::Plant1:          return {   0, 224, 32, 32 };
            case TileImage::Plant2:          return {  32, 224, 32, 32 };
            case TileImage::Plant3:          return {  64, 224, 32, 32 };
            case TileImage::Plant4:          return {  96, 224, 32, 32 };
            case TileImage::SnakeBag:        return { 192,  64, 32, 32 };
            case TileImage::Snake:           return { 224,  64, 32, 32 };
            case TileImage::SpiderWeb:       return { 192,  96, 32, 32 };
            case TileImage::Spider:          return { 224,  96, 32, 32 };
            case TileImage::GoblinPot:       return { 192, 128, 32, 32 };
            case TileImage::Goblin:          return { 224, 128, 32, 32 };
            case TileImage::BirdMask:        return { 192, 160, 32, 32 };
            case TileImage::Bat:             return { 224, 160, 32, 32 };
            case TileImage::SkeletonGrave:   return { 192, 192, 32, 32 };
            case TileImage::Skeleton:        return { 224, 192, 32, 32 };
            case TileImage::DemonDoor:       return { 192, 224, 32, 32 };
            case TileImage::Demon:           return { 224, 224, 32, 32 };
            case TileImage::DragonBreath:    return { 128, 224, 32, 32 };
            case TileImage::Dragon:          return { 160, 224, 32, 32 };
            case TileImage::Empty:           
            case TileImage::Count:
            default:                         return { 128,  96, 32, 32 };
        }
        // clang-format on
    }

} // namespace castlecrawl
#endif // CASTLECRAWL_TILEIMAGE_HPP_INCLUDED
