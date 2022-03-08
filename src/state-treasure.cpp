// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-treasure.cpp
//
#include "state-treasure.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "media.hpp"
#include "player.hpp"
#include "popup-manager.hpp"
#include "settings.hpp"
#include "state-machine.hpp"
#include "util.hpp"

namespace castlecrawl
{
    StateTreasure::StateTreasure(Context & context)
        : StatePlay(context)
        , m_bgFadeVerts()
    {}

    void StateTreasure::onEnter(Context & context)
    {
        context.player.adjGold(treasure.gold);

        util::appendQuadVerts(
            context.layout.windowBounds(), m_bgFadeVerts, sf::Color(0, 0, 0, 150));

        const TextBlock textBlock =
            context.media.makeTextBlock(FontSize::Medium, treasure.description());

        m_texts = textBlock.lines;

        m_bgRectangle.setFillColor(sf::Color(25, 100, 115, 200));
        m_bgRectangle.setOutlineColor(sf::Color(255, 255, 255, 200));
        m_bgRectangle.setOutlineThickness(2.0f);
        m_bgRectangle.setPosition(0.0f, (context.layout.windowSize().y * 0.2f));

        std::string titleStr{ "Treasure!" };
        if (treasure.empty())
        {
            titleStr.clear();
        }

        m_titleText = context.media.makeText(FontSize::Large, titleStr);

        const float vertPad{ context.layout.windowSize().y * 0.015f };

        const sf::Vector2f titlePos{ ((context.layout.windowSize().x * 0.5f) -
                                      (m_titleText.getGlobalBounds().width * 0.5f)),
                                     (m_bgRectangle.getGlobalBounds().top + vertPad) };

        m_titleText.setPosition(titlePos);

        const sf::Vector2f listPos{ ((context.layout.windowSize().x * 0.5f) -
                                     (textBlock.size.x * 0.5f)),
                                    (util::bottom(m_titleText) + vertPad) };

        for (sf::Text & text : m_texts)
        {
            text.move(listPos);
        }

        const float bgRectangleHeight{
            (util::bottom(m_texts.back()) - m_bgRectangle.getGlobalBounds().top) + vertPad
        };

        m_bgRectangle.setSize(sf::Vector2f{ context.layout.windowSize().x, bgRectangleHeight });
    }

    void StateTreasure::onExit(Context &) { treasure = {}; }

    void StateTreasure::handleEvent(Context & context, const sf::Event & event)
    {
        if (sf::Event::KeyPressed != event.type)
        {
            return;
        }

        if (sf::Keyboard::Escape == event.key.code)
        {
            context.state.setChangePending(State::Play);
            return;
        }
    }

    void StateTreasure::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        StatePlay::draw(context, target, states);
        target.draw(&m_bgFadeVerts[0], m_bgFadeVerts.size(), sf::PrimitiveType::Quads);
        target.draw(m_bgRectangle, states);
        target.draw(m_titleText, states);

        for (const sf::Text & text : m_texts)
        {
            target.draw(text, states);
        }
    }

} // namespace castlecrawl
