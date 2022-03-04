#ifndef CASTLECRAWL_MEDIA_HPP_INCLUDED
#define CASTLECRAWL_MEDIA_HPP_INCLUDED
//
// media.hpp
//
#include "check-macros.hpp"
#include "sound-player.hpp"
#include "tile-image.hpp"

#include <filesystem>
#include <string>
#include <vector>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace util
{
    class SoundPlayer;
    class AnimationPlayer;
} // namespace util

namespace castlecrawl
{
    struct Context;
    struct GameConfig;
    class Layout;

    enum class FontSize
    {
        Huge,
        Large,
        Medium,
        Small
    };

    struct TextBlock
    {
        sf::Vector2f size;
        std::vector<sf::Text> lines;
    };

    struct FontExtent
    {
        unsigned int char_size = 0;
        sf::Vector2f letter_size;
    };

    class Media
    {
      public:
        Media() = default;

        void load(const GameConfig &, const Layout &, util::SoundPlayer &);

        const sf::Font & font() const;
        const sf::Sprite & sprite(const TileImage) const;
        const sf::Texture & tileTexture() const { return m_tileTexture; }
        const FontExtent fontExtent(const FontSize size) const;

        const sf::Text makeText(
            const FontSize size,
            const std::string & singleLineMessage,
            const sf::Color & color = sf::Color::White) const;

        const TextBlock makeTextBlock(
            const FontSize size,
            const std::string & multiLineMessage,
            const sf::Color & color = sf::Color::White) const;

      protected:
        void makeDefaults();
        void loadTileSprites(const GameConfig & config, const Layout &);
        void calcFontExtents();

        template <typename T>
        void load(const std::filesystem::path & path, T & loadable)
        {
            M_CHECK(std::filesystem::exists(path), path);
            M_CHECK(std::filesystem::is_regular_file(path), path);

            const bool loadSuccess{ loadable.loadFromFile(path.string()) };
            M_CHECK(loadSuccess, path);
        }

      protected:
        sf::Font m_font;
        std::vector<sf::Sprite> m_tileSprites;
        sf::Texture m_tileTexture;

        FontExtent m_fontExtentHuge;
        FontExtent m_fontExtentLarge;
        FontExtent m_fontExtentMedium;
        FontExtent m_fontExtentSmall;

        static inline sf::Texture m_defaultTexture;
        static inline sf::Sprite m_defaultSprite;
    };

} // namespace castlecrawl

#endif // #define CASTLECRAWL_MEDIA_HPP_INCLUDED
