#ifndef CASTLECRAWL_MEDIA_HPP_INCLUDED
#define CASTLECRAWL_MEDIA_HPP_INCLUDED
//
// media.hpp
//
#include "check-macros.hpp"
#include "splat-image.hpp"
#include "summon-image.hpp"
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

    //

    class Media
    {
      public:
        Media() = default;

        void load(const GameConfig &, const Layout &, util::SoundPlayer &);

        const sf::Font & font() const;
        const sf::Sprite & tileSprite(const TileImage image) const;
        const sf::Sprite & summonSprite(const SummonImage image) const;

        const sf::Texture & tileTexture() const { return m_tileTexture; }
        const sf::Texture & titleTexture() const { return m_titleTexture; }
        const sf::Texture & paper1Texture() const { return m_paper1Texture; }
        const sf::Texture & paper2Texture() const { return m_paper2Texture; }

        const sf::Sprite & splatSprite(const SplatImage image) const;

        const sf::FloatRect paper1InnerRect() const { return { 32.0f, 32.0f, 436.0f, 266.0f }; }
        const sf::FloatRect paper2InnerRect() const { return { 32.0f, 32.0f, 430.0f, 430.0f }; }

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
        void loadTileSprites(const GameConfig & config, const Layout & layout);
        void loadSummonSprites(const GameConfig & config, const Layout & layout);
        void loadSplatSprites(const GameConfig & config, const Layout & layout);

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

        sf::Texture m_tileTexture;
        std::vector<sf::Sprite> m_tileSprites;

        sf::Texture m_summonTexture;
        std::vector<sf::Sprite> m_summonSprites;

        FontExtent m_fontExtentHuge;
        FontExtent m_fontExtentLarge;
        FontExtent m_fontExtentMedium;
        FontExtent m_fontExtentSmall;

        sf::Texture m_titleTexture;
        sf::Texture m_paper1Texture;
        sf::Texture m_paper2Texture;

        sf::Texture m_splatTexture;
        std::vector<sf::Sprite> m_splatSprites;

        static inline sf::Texture m_defaultTexture;
        static inline sf::Sprite m_defaultSprite;
    };

} // namespace castlecrawl

#endif // #define CASTLECRAWL_MEDIA_HPP_INCLUDED
