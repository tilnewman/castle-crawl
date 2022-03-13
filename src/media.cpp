// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// media.cpp
//
#include "media.hpp"

#include "config.hpp"
#include "context.hpp"
#include "settings.hpp"
#include "sound-player.hpp"
#include "util.hpp"

namespace castlecrawl
{
    void Media::load(const GameConfig & config, const Layout & layout, util::SoundPlayer & audio)
    {
        makeDefaults();

        load((config.media_dir_path / "font/gentium-plus/gentium-plus.ttf"), m_font);
        calcFontExtents();

        loadTileSprites(config, layout);
        loadSummonSprites(config, layout);

        load((config.media_dir_path / "image" / "title.png"), m_titleTexture);
        load((config.media_dir_path / "image" / "paper-1.png"), m_paper1Texture);
        load((config.media_dir_path / "image" / "paper-2.png"), m_paper2Texture);

        audio.loadAll();
    }

    void Media::loadTileSprites(const GameConfig & config, const Layout & layout)
    {
        const std::size_t imageCount = static_cast<std::size_t>(TileImage::Count);
        m_tileSprites.resize(imageCount);

        load((config.media_dir_path / "image" / "tile.png"), m_tileTexture);

        for (std::size_t i(0); i < imageCount; ++i)
        {
            m_tileSprites[i].setTexture(m_tileTexture);
            m_tileSprites[i].setTextureRect(tileImageToTileRect(static_cast<TileImage>(i)));
            util::fit(m_tileSprites[i], layout.mapCellSize());
        }

        m_tileSprites.at(static_cast<std::size_t>(TileImage::Coffin))
            .setColor(sf::Color(130, 75, 40));

        m_tileSprites.at(static_cast<std::size_t>(TileImage::Empty)) = m_defaultSprite;
    }

    void Media::loadSummonSprites(const GameConfig & config, const Layout & layout)
    {
        const std::size_t imageCount{ static_cast<std::size_t>(SummonImage::Count) };
        m_summonSprites.resize(imageCount);

        load((config.media_dir_path / "image" / "summon.png"), m_summonTexture);

        for (std::size_t i(0); i < imageCount; ++i)
        {
            m_summonSprites[i].setTexture(m_summonTexture);
            m_summonSprites[i].setTextureRect(summonImageRect(static_cast<SummonImage>(i)));
            util::fit(m_summonSprites[i], layout.mapCellSize());
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

    const sf::Sprite & Media::summonSprite(const SummonImage image) const
    {
        const std::size_t index = static_cast<std::size_t>(image);
        if (index < m_summonSprites.size())
        {
            return m_summonSprites[index];
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
        m_defaultSprite.setTexture(m_defaultTexture, true);
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

    void Media::calcFontExtents()
    {
        sf::Text text;
        const std::string widthStr{ "M" };
        const std::string heightStr{ "|g" };

        m_fontExtentHuge.char_size = 120;
        text = makeText(FontSize::Huge, widthStr);
        m_fontExtentHuge.letter_size.x = text.getGlobalBounds().width;
        text = makeText(FontSize::Huge, heightStr);
        m_fontExtentHuge.letter_size.y = text.getGlobalBounds().height;

        m_fontExtentLarge.char_size = 80;
        text = makeText(FontSize::Large, widthStr);
        m_fontExtentLarge.letter_size.x = text.getGlobalBounds().width;
        text = makeText(FontSize::Large, heightStr);
        m_fontExtentLarge.letter_size.y = text.getGlobalBounds().height;

        m_fontExtentMedium.char_size = 50;
        text = makeText(FontSize::Medium, widthStr);
        m_fontExtentMedium.letter_size.x = text.getGlobalBounds().width;
        text = makeText(FontSize::Medium, heightStr);
        m_fontExtentMedium.letter_size.y = text.getGlobalBounds().height;

        m_fontExtentSmall.char_size = 30;
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
