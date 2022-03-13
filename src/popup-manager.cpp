// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// popup-manager.cpp
//
#include "popup-manager.hpp"

#include "context.hpp"
#include "gui-text.hpp"
#include "layout.hpp"
#include "media.hpp"
#include "util.hpp"

namespace castlecrawl
{

    void PopupManager::setupBanner(Context & context, const std::string & message)
    {
        const TextBlock textBlock = context.media.makeTextBlock(FontSize::Medium, message);
        m_texts = textBlock.lines;

        m_fadeRectangle.setSize(context.layout.windowSize());
        m_fadeRectangle.setFillColor(sf::Color(0, 0, 0, 64));

        m_bgRectangle.setFillColor(sf::Color(25, 100, 115, 200));
        m_bgRectangle.setOutlineColor(sf::Color(255, 255, 255, 200));
        m_bgRectangle.setOutlineThickness(2.0f);
        m_bgRectangle.setPosition(0.0f, (context.layout.windowSize().y * 0.2f));

        const float vertPad{ context.layout.windowSize().y * 0.015f };

        const sf::Vector2f pos{ ((context.layout.windowSize().x * 0.5f) -
                                 (textBlock.size.x * 0.5f)),
                                (m_bgRectangle.getGlobalBounds().top + vertPad) };

        for (sf::Text & text : m_texts)
        {
            text.move(pos);
        }

        const float bgRectangleHeight{ (util::bottom(m_texts.back().getGlobalBounds()) -
                                        m_bgRectangle.getGlobalBounds().top) +
                                       vertPad };

        m_bgRectangle.setSize(sf::Vector2f{ context.layout.windowSize().x, bgRectangleHeight });

        m_paperSprite = {};
    }

    void PopupManager::setupPaper(
        Context & context,
        const PopupBackground background,
        const FontSize fontSize,
        const sf::Color & color,
        const std::string & text)
    {
        m_fadeRectangle.setSize(context.layout.windowSize());
        m_fadeRectangle.setFillColor(sf::Color(0, 0, 0, 64));

        m_bgRectangle.setFillColor(sf::Color::Transparent);
        m_bgRectangle.setOutlineColor(sf::Color::Transparent);
        m_bgRectangle.setOutlineThickness(0.0f);
        m_bgRectangle.setSize({ 0.0f, 0.0f });

        m_paperSprite = [&]() {
            if (PopupBackground::Paper1 == background)
            {
                return sf::Sprite(context.media.paper1Texture());
            }
            else
            {
                return sf::Sprite(context.media.paper2Texture());
            }
        }();

        const sf::Vector2f windowSize{ context.layout.windowSize() };
        const float paperWidth{ windowSize.x * 0.3f };

        const sf::FloatRect sizingRect{
            ((windowSize.x * 0.5f) - (paperWidth * 0.5f)), 0.0f, paperWidth, windowSize.y
        };

        util::fitAndCenterInside(m_paperSprite, sizingRect);

        sf::FloatRect textRegion = [&]() {
            if (PopupBackground::Paper1 == background)
            {
                return context.media.paper1InnerRect();
            }
            else
            {
                return context.media.paper2InnerRect();
            }
        }();

        const float paperLocalWidth{ static_cast<float>(m_paperSprite.getLocalBounds().width) };
        const float resizeRatio{ 1.0f - ((paperLocalWidth - paperWidth) / paperLocalWidth) };

        textRegion.left *= resizeRatio;
        textRegion.top *= resizeRatio;
        textRegion.width *= resizeRatio;
        textRegion.height *= resizeRatio;

        textRegion.left += util::position(m_paperSprite).x;
        textRegion.top += util::position(m_paperSprite).y;

        m_texts = typeset(context, fontSize, color, textRegion, text);
    }

    void PopupManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_fadeRectangle, states);
        target.draw(m_bgRectangle, states);
        target.draw(m_paperSprite, states);

        for (const sf::Text & text : m_texts)
        {
            target.draw(text, states);
        }
    }

} // namespace castlecrawl
