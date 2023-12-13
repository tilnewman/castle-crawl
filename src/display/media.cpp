// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// media.cpp
//
#include "display/media.hpp"

#include "audio/sound-player.hpp"
#include "display/layout.hpp"
#include "misc/config.hpp"
#include "misc/context.hpp"
#include "misc/random.hpp"
#include "misc/sfml-util.hpp"

namespace castlecrawl
{
    void Media::load(const GameConfig & config, const Layout & layout, util::SoundPlayer & audio)
    {
        makeDefaults();

        load((config.media_dir_path / "font/gentium-plus/gentium-plus.ttf"), m_font);
        calcFontExtents(layout);

        loadTileSprites(config, layout);
        loadSplatSprites(config, layout);

        load((config.media_dir_path / "image" / "title.png"), m_titleTexture);
        load((config.media_dir_path / "image" / "paper-1.png"), m_paper1Texture);
        load((config.media_dir_path / "image" / "paper-2.png"), m_paper2Texture);
        load((config.media_dir_path / "image" / "enemy.png"), m_enemyTexture);

        m_titleTexture.setSmooth(true);
        m_paper1Texture.setSmooth(true);
        m_paper2Texture.setSmooth(true);
        m_enemyTexture.setSmooth(true);

        audio.loadAll();
    }

    void Media::loadTileSprites(const GameConfig & config, const Layout & layout)
    {
        const std::size_t imageCount = static_cast<std::size_t>(TileImage::Count);
        m_tileSprites.resize(imageCount);

        load((config.media_dir_path / "image" / "tile.png"), m_tileTexture);

        for (std::size_t i(0); i < imageCount; ++i)
        {
            // intentionally don't setSmooth(true) to avoid strange line artifacts
            m_tileSprites[i].setTexture(m_tileTexture);
            m_tileSprites[i].setTextureRect(tileImageToTileRect(static_cast<TileImage>(i)));
            util::fit(m_tileSprites[i], layout.mapCellSize());
        }

        m_tileSprites.at(static_cast<std::size_t>(TileImage::Coffin))
            .setColor(sf::Color(180, 125, 90));

        m_tileSprites.at(static_cast<std::size_t>(TileImage::Empty)) = m_defaultSprite;
    }

    void Media::loadSplatSprites(const GameConfig & config, const Layout & layout)
    {
        const std::size_t imageCount{ static_cast<std::size_t>(SplatImage::Count) };
        m_splatSprites.resize(imageCount);

        load((config.media_dir_path / "image" / "splat.png"), m_splatTexture);
        m_splatTexture.setSmooth(true);

        for (std::size_t i(0); i < imageCount; ++i)
        {
            m_splatSprites[i].setTexture(m_splatTexture);
            m_splatSprites[i].setTextureRect(splatImageRect(static_cast<SplatImage>(i)));
            m_splatSprites[i].setColor(sf::Color(255, 0, 0, 200));
            util::fit(m_splatSprites[i], layout.mapCellSize());
        }
    }

    const sf::Font & Media::font() const { return m_font; }

    const sf::Sprite & Media::tileSprite(const TileImage image) const
    {
        const std::size_t index = static_cast<std::size_t>(image);
        if (index < m_tileSprites.size())
        {
            return m_tileSprites[index];
        }
        else
        {
            return m_defaultSprite;
        }
    }

    const sf::Sprite Media::enemySprite(const Context & context, const Pieces enemyPiece) const
    {
        sf::Sprite sprite(m_enemyTexture);

        if (enemyPiece == Pieces::Snake)
        {
            sprite.setTextureRect(textureRect(static_cast<EnemyImage>(
                static_cast<int>(EnemyImage::Snake1) + context.random.zeroTo(5))));
        }
        else if (enemyPiece == Pieces::Spider)
        {
            sprite.setTextureRect(textureRect(static_cast<EnemyImage>(
                static_cast<int>(EnemyImage::Spider1) + context.random.zeroTo(5))));
        }
        else if (enemyPiece == Pieces::Goblin)
        {
            sprite.setTextureRect(textureRect(static_cast<EnemyImage>(
                static_cast<int>(EnemyImage::Goblin1) + context.random.zeroTo(5))));
        }
        else if (enemyPiece == Pieces::Bat)
        {
            sprite.setTextureRect(textureRect(static_cast<EnemyImage>(
                static_cast<int>(EnemyImage::Bat1) + context.random.zeroTo(5))));
        }
        else if (enemyPiece == Pieces::Pixie)
        {
            sprite.setTextureRect(textureRect(static_cast<EnemyImage>(
                static_cast<int>(EnemyImage::Pixie1) + context.random.zeroTo(5))));
        }
        else if (enemyPiece == Pieces::Skeleton)
        {
            sprite.setTextureRect(textureRect(static_cast<EnemyImage>(
                static_cast<int>(EnemyImage::Skeleton1) + context.random.zeroTo(5))));
        }
        else if (enemyPiece == Pieces::Demon)
        {
            sprite.setTextureRect(textureRect(static_cast<EnemyImage>(
                static_cast<int>(EnemyImage::Demon1) + context.random.zeroTo(5))));
        }
        else if (enemyPiece == Pieces::Dragon)
        {
            sprite.setTextureRect(textureRect(static_cast<EnemyImage>(
                static_cast<int>(EnemyImage::Dragon1) + context.random.zeroTo(5))));
        }
        else if (enemyPiece == Pieces::Wizard)
        {
            sprite.setTextureRect(textureRect(static_cast<EnemyImage>(
                static_cast<int>(EnemyImage::Wizard1) + context.random.zeroTo(5))));
        }
        else
        {
            sprite.setTextureRect(textureRect(EnemyImage::FireLord));
        }

        util::fit(sprite, context.layout.mapCellSize());
        return sprite;
    }

    const sf::Sprite & Media::splatSprite(const SplatImage image) const
    {
        const std::size_t index = static_cast<std::size_t>(image);
        if (index < m_splatSprites.size())
        {
            return m_splatSprites[index];
        }
        else
        {
            return m_defaultSprite;
        }
    }

    void Media::makeDefaults()
    {
        sf::Image image;
        image.create(1, 1, sf::Color::White);
        m_defaultTexture.loadFromImage(image);
        m_defaultSprite.setTexture(m_defaultTexture);
    }

    const FontExtent Media::fontExtent(const FontSize size) const
    {
        if (size == FontSize::Huge)
        {
            return m_fontExtentHuge;
        }
        else if (size == FontSize::Large)
        {
            return m_fontExtentLarge;
        }
        else if (size == FontSize::Medium)
        {
            return m_fontExtentMedium;
        }
        else
        {
            return m_fontExtentSmall;
        }
    }

    void Media::calcFontExtents(const Layout & layout)
    {
        const float standardRes = std::sqrt(3840.f * 2400.0f);
        const float currentRes = std::sqrt(layout.windowSize().x * layout.windowSize().y);
        const float ratioRes = (currentRes / standardRes);

        sf::Text text;
        const std::string widthStr{ "M" };
        const std::string heightStr{ "|g" };

        m_fontExtentHuge.char_size = static_cast<unsigned>(130.0f * ratioRes);
        text = makeText(FontSize::Huge, widthStr);
        m_fontExtentHuge.letter_size.x = text.getGlobalBounds().width;
        text = makeText(FontSize::Huge, heightStr);
        m_fontExtentHuge.letter_size.y = text.getGlobalBounds().height;

        m_fontExtentLarge.char_size = static_cast<unsigned>(90.0f * ratioRes);
        text = makeText(FontSize::Large, widthStr);
        m_fontExtentLarge.letter_size.x = text.getGlobalBounds().width;
        text = makeText(FontSize::Large, heightStr);
        m_fontExtentLarge.letter_size.y = text.getGlobalBounds().height;

        m_fontExtentMedium.char_size = static_cast<unsigned>(60.0f * ratioRes);
        text = makeText(FontSize::Medium, widthStr);
        m_fontExtentMedium.letter_size.x = text.getGlobalBounds().width;
        text = makeText(FontSize::Medium, heightStr);
        m_fontExtentMedium.letter_size.y = text.getGlobalBounds().height;

        m_fontExtentSmall.char_size = static_cast<unsigned>(40.0f * ratioRes);
        text = makeText(FontSize::Small, widthStr);
        m_fontExtentSmall.letter_size.x = text.getGlobalBounds().width;
        text = makeText(FontSize::Small, heightStr);
        m_fontExtentSmall.letter_size.y = text.getGlobalBounds().height;
    }

    const sf::Text Media::makeText(
        const FontSize size, const std::string & singleLineMessage, const sf::Color & color) const
    {
        const FontExtent extent = fontExtent(size);
        sf::Text text(singleLineMessage, m_font, extent.char_size);
        text.setFillColor(color);
        util::setOriginToPosition(text);
        return text;
    }

    const TextBlock Media::makeTextBlock(
        const FontSize size, const std::string & multiLineMessage, const sf::Color & color) const
    {
        std::vector<std::string> strings;
        strings.resize(1);

        for (const char ch : multiLineMessage)
        {
            if (ch == '\n')
            {
                strings.push_back("");
            }
            else
            {
                strings.back().push_back(ch);
            }
        }

        TextBlock textBlock;
        float posY = 0.0f;
        for (std::string & lineStr : strings)
        {
            if (lineStr.empty())
            {
                lineStr.push_back(' ');
            }

            sf::Text & text = textBlock.lines.emplace_back(makeText(size, lineStr, color));
            const sf::FloatRect bounds = text.getGlobalBounds();

            if (bounds.width > textBlock.size.x)
            {
                textBlock.size.x = bounds.width;
            }

            textBlock.size.y += bounds.height;

            text.setPosition(0.0f, posY);
            posY += fontExtent(size).letter_size.y;
            posY += (text.getGlobalBounds().height * 0.1f);
        }

        return textBlock;
    }

} // namespace castlecrawl
