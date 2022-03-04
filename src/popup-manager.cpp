// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// popup-manager.cpp
//
#include "popup-manager.hpp"

#include "context.hpp"
#include "media.hpp"
#include "settings.hpp"
#include "util.hpp"

namespace castlecrawl
{

    void PopupManager::setup(Context & context, const std::string & message)
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
    }

    void PopupManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_fadeRectangle, states);
        target.draw(m_bgRectangle, states);

        for (const sf::Text & text : m_texts)
        {
            target.draw(text, states);
        }
    }

} // namespace castlecrawl
