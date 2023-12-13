#ifndef CASTLECRAWL_MEDIA_HPP_INCLUDED
#define CASTLECRAWL_MEDIA_HPP_INCLUDED
//
// media.hpp
//
#include "display/splat-image.hpp"
#include "display/tile-image.hpp"
#include "map/pieces.hpp"
#include "misc/check-macros.hpp"

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

    enum class EnemyImage
    {
        Snake1,
        Snake2,
        Snake3,
        Snake4,
        Snake5,
        Snake6,
        Spider1,
        Spider2,
        Spider3,
        Spider4,
        Spider5,
        Spider6,
        Goblin1,
        Goblin2,
        Goblin3,
        Goblin4,
        Goblin5,
        Goblin6,
        Bat1,
        Bat2,
        Bat3,
        Bat4,
        Bat5,
        Bat6,
        Pixie1,
        Pixie2,
        Pixie3,
        Pixie4,
        Pixie5,
        Pixie6,
        Skeleton1,
        Skeleton2,
        Skeleton3,
        Skeleton4,
        Skeleton5,
        Skeleton6,
        Demon1,
        Demon2,
        Demon3,
        Demon4,
        Demon5,
        Demon6,
        Dragon1,
        Dragon2,
        Dragon3,
        Dragon4,
        Dragon5,
        Dragon6,
        Wizard1,
        Wizard2,
        Wizard3,
        Wizard4,
        Wizard5,
        Wizard6,
        FireLord
    };

    inline const sf::IntRect textureRect(const EnemyImage enemyImage) noexcept
    {
        // clang-format off
        switch (enemyImage)
        {
            case EnemyImage::Snake1:        { return {  64,   0, 64, 64}; }
            case EnemyImage::Snake2:        { return { 128,   0, 64, 64}; }
            case EnemyImage::Snake3:        { return { 192,   0, 64, 64}; }
            case EnemyImage::Snake4:        { return { 256,   0, 64, 64}; }
            case EnemyImage::Snake5:        { return { 320,   0, 64, 64}; }
            case EnemyImage::Snake6:        { return { 384,   0, 64, 64}; }
            case EnemyImage::Spider1:       { return {  64,  64, 64, 64}; }
            case EnemyImage::Spider2:       { return { 128,  64, 64, 64}; }
            case EnemyImage::Spider3:       { return { 192,  64, 64, 64}; }
            case EnemyImage::Spider4:       { return { 256,  64, 64, 64}; }
            case EnemyImage::Spider5:       { return { 320,  64, 64, 64}; }
            case EnemyImage::Spider6:       { return { 384,  64, 64, 64}; }
            case EnemyImage::Goblin1:       { return {  64, 128, 64, 64}; }
            case EnemyImage::Goblin2:       { return { 128, 128, 64, 64}; }
            case EnemyImage::Goblin3:       { return { 192, 128, 64, 64}; }
            case EnemyImage::Goblin4:       { return { 256, 128, 64, 64}; }
            case EnemyImage::Goblin5:       { return { 320, 128, 64, 64}; }
            case EnemyImage::Goblin6:       { return { 384, 128, 64, 64}; }
            case EnemyImage::Bat1:          { return {  64, 192, 64, 64}; }
            case EnemyImage::Bat2:          { return { 128, 192, 64, 64}; }
            case EnemyImage::Bat3:          { return { 192, 192, 64, 64}; }
            case EnemyImage::Bat4:          { return { 256, 192, 64, 64}; }
            case EnemyImage::Bat5:          { return { 320, 192, 64, 64}; }
            case EnemyImage::Bat6:          { return { 384, 192, 64, 64}; }
            case EnemyImage::Pixie1:        { return {  64, 256, 64, 64}; }
            case EnemyImage::Pixie2:        { return { 128, 256, 64, 64}; }
            case EnemyImage::Pixie3:        { return { 192, 256, 64, 64}; }
            case EnemyImage::Pixie4:        { return { 256, 256, 64, 64}; }
            case EnemyImage::Pixie5:        { return { 320, 256, 64, 64}; }
            case EnemyImage::Pixie6:        { return { 384, 256, 64, 64}; }
            case EnemyImage::Skeleton1:     { return {  64, 320, 64, 64}; }
            case EnemyImage::Skeleton2:     { return { 128, 320, 64, 64}; }
            case EnemyImage::Skeleton3:     { return { 192, 320, 64, 64}; }
            case EnemyImage::Skeleton4:     { return { 256, 320, 64, 64}; }
            case EnemyImage::Skeleton5:     { return { 320, 320, 64, 64}; }
            case EnemyImage::Skeleton6:     { return { 384, 320, 64, 64}; }
            case EnemyImage::Demon1:        { return {  64, 384, 64, 64}; }
            case EnemyImage::Demon2:        { return { 128, 384, 64, 64}; }
            case EnemyImage::Demon3:        { return { 192, 384, 64, 64}; }
            case EnemyImage::Demon4:        { return { 256, 384, 64, 64}; }
            case EnemyImage::Demon5:        { return { 320, 384, 64, 64}; }
            case EnemyImage::Demon6:        { return { 384, 384, 64, 64}; }
            case EnemyImage::Dragon1:       { return {  64, 448, 64, 64}; }
            case EnemyImage::Dragon2:       { return { 128, 448, 64, 64}; }
            case EnemyImage::Dragon3:       { return { 192, 448, 64, 64}; }
            case EnemyImage::Dragon4:       { return { 256, 448, 64, 64}; }
            case EnemyImage::Dragon5:       { return { 320, 448, 64, 64}; }
            case EnemyImage::Dragon6:       { return { 384, 448, 64, 64}; }
            case EnemyImage::Wizard1:       { return { 448,  64, 64, 64}; }
            case EnemyImage::Wizard2:       { return { 448, 128, 64, 64}; }
            case EnemyImage::Wizard3:       { return { 448, 192, 64, 64}; }
            case EnemyImage::Wizard4:       { return { 448, 256, 64, 64}; }
            case EnemyImage::Wizard5:       { return { 448, 320, 64, 64}; }
            case EnemyImage::Wizard6:       { return { 448, 384, 64, 64}; }
            case EnemyImage::FireLord:
            default:                        { return { 224, 224, 64, 64}; }
        }
        // clang-format on
    }

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

        const sf::Texture & tileTexture() const { return m_tileTexture; }
        const sf::Texture & titleTexture() const { return m_titleTexture; }
        const sf::Texture & paper1Texture() const { return m_paper1Texture; }
        const sf::Texture & paper2Texture() const { return m_paper2Texture; }
        const sf::Sprite enemySprite(const Context & context, const Pieces enemyPiece) const;

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
        void loadSplatSprites(const GameConfig & config, const Layout & layout);

        void calcFontExtents(const Layout & layout);

        template <typename T>
        void load(const std::filesystem::path & path, T & loadable)
        {
            M_CHECK(std::filesystem::exists(path), path);
            M_CHECK(std::filesystem::is_regular_file(path), path);

            const bool loadSuccess{ loadable.loadFromFile(path.string()) };

            // this causes artifacts between tile sprites so don't do it
            // if constexpr (std::is_same_v<T, sf::Texture>)
            //{
            //    loadable.setSmooth(true);
            //}

            M_CHECK(loadSuccess, path);
        }

      protected:
        sf::Font m_font;

        sf::Texture m_tileTexture;
        std::vector<sf::Sprite> m_tileSprites;

        FontExtent m_fontExtentHuge;
        FontExtent m_fontExtentLarge;
        FontExtent m_fontExtentMedium;
        FontExtent m_fontExtentSmall;

        sf::Texture m_titleTexture;
        sf::Texture m_paper1Texture;
        sf::Texture m_paper2Texture;
        sf::Texture m_enemyTexture;

        sf::Texture m_splatTexture;
        std::vector<sf::Sprite> m_splatSprites;

        static inline sf::Texture m_defaultTexture;
        static inline sf::Sprite m_defaultSprite;
    };

} // namespace castlecrawl

#endif // #define CASTLECRAWL_MEDIA_HPP_INCLUDED
