#ifndef CASTLECRAWLMAPPER_RESOURCES_HPP_INCLUDED
#define CASTLECRAWLMAPPER_RESOURCES_HPP_INCLUDED
//
// resources.hpp
//
#include "../src/check-macros.hpp"
#include "context.hpp"
#include "sound-player.hpp"
#include "tile-image.hpp"

#include <filesystem>

#include <SFML/Graphics.hpp>

//

namespace util
{
    class SoundPlayer;
    class AnimationPlayer;
} // namespace util

//

namespace castlecrawl
{
    struct GameConfig;
    class Layout;

    class Media
    {
      public:
        Media() = default;

        void load(const GameConfig &, const Layout &);

        const sf::Font & font() const;
        const sf::Sprite & sprite(const TileImage) const;
        const sf::Texture & tileTexture() const { return m_tileTexture; }

      protected:
        void makeDefaults();
        void loadSoundEffects(util::SoundPlayer &);
        void loadTileSprites(const GameConfig & config, const Layout &);

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

        static inline sf::Texture m_defaultTexture;
        static inline sf::Sprite m_defaultSprite;
    };

} // namespace castlecrawl

#endif // #define CASTLECRAWLMAPPER_RESOURCES_HPP_INCLUDED
