#ifndef CASTLECRAWL_SPLAT_IMAGE_HPP_INCLUDED
#define CASTLECRAWL_SPLAT_IMAGE_HPP_INCLUDED
//
// splat-image.hpp
//
#include <cstddef>

#include <SFML/Graphics/Rect.hpp>

namespace castlecrawl
{
    // used to index so keep unsigned
    enum class SplatImage : std::size_t
    {
        Splat0 = 0,
        Splat1,
        Splat2,
        Splat3,
        Splat4,
        Splat5,
        Count
    };

    inline sf::IntRect splatImageRect(const SplatImage image) noexcept
    {
        // clang-format off
        switch (image)
        {
            case SplatImage::Splat0: return sf::IntRect( 0,0,64,64);
            case SplatImage::Splat1: return sf::IntRect(64,0,64,64);
            case SplatImage::Splat2: return sf::IntRect(128,0,64,64);
            case SplatImage::Splat3: return sf::IntRect( 0,64,64,64);
            case SplatImage::Splat4: return sf::IntRect(64,64,64,64);
            case SplatImage::Splat5: return sf::IntRect(128,64,64,64);
            //
            case SplatImage::Count:
            default:                 return sf::IntRect(0,0,0,0);
        }
        // clang-format on
    }

} // namespace castlecrawl
#endif // CASTLECRAWL_TILEIMAGE_HPP_INCLUDED
