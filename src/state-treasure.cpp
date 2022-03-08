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
        , m_titleText()
        , m_goldText()
        , m_itemTexts()
        , m_bgRectangle()
    {}

    void StateTreasure::onEnter(Context & context)
    {
        // always take the gold even if you don't take any items
        context.player.adjGold(treasure.gold);

        // fade out the background
        util::appendQuadVerts(
            context.layout.windowBounds(), m_bgFadeVerts, sf::Color(0, 0, 0, 150));

        // cyan bluish bar so the text can be white on top of it
        m_bgRectangle.setFillColor(sf::Color(25, 100, 115, 200));
        m_bgRectangle.setOutlineColor(sf::Color(255, 255, 255, 200));
        m_bgRectangle.setOutlineThickness(2.0f);
        m_bgRectangle.setPosition(0.0f, (context.layout.windowSize().y * 0.2f));

        // title text
        std::string titleStr{ "Treasure" };
        if (treasure.empty())
        {
            titleStr.clear();
        }

        m_titleText = context.media.makeText(FontSize::Large, titleStr);

        const float vertPad{ context.layout.windowSize().y * 0.015f };

        m_titleText.setPosition(
            ((context.layout.windowSize().x * 0.5f) - (m_titleText.getGlobalBounds().width * 0.5f)),
            (m_bgRectangle.getGlobalBounds().top + vertPad));

        // gold text
        std::string goldStr;
        if (treasure.empty())
        {
            goldStr = "You find nothing.";
        }
        else if (treasure.gold > 0)
        {
            goldStr = "You find ";
            goldStr += std::to_string(treasure.gold);
            goldStr += " gold coins";

            if (treasure.items.empty())
            {
                goldStr += '.';
            }
            else
            {
                goldStr += " and:";
            }
        }

        m_goldText = context.media.makeText(FontSize::Medium, goldStr);

        m_goldText.setPosition(
            ((context.layout.windowSize().x * 0.5f) - (m_goldText.getGlobalBounds().width * 0.5f)),
            (util::bottom(m_titleText) + vertPad));

        // item texts
        float itemTextPosY{ util::bottom(m_goldText) + vertPad };
        for (const item::Item & item : treasure.items)
        {
            sf::Text & text =
                m_itemTexts.emplace_back(context.media.makeText(FontSize::Medium, item.name()));

            text.setPosition(
                ((context.layout.windowSize().x * 0.5f) - (text.getGlobalBounds().width * 0.5f)),
                itemTextPosY);

            itemTextPosY += context.media.fontExtent(FontSize::Medium).letter_size.y;
        }

        const float bgRectangleHeight{ (itemTextPosY - m_bgRectangle.getGlobalBounds().top) +
                                       vertPad };

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
        target.draw(m_goldText, states);

        for (const sf::Text & text : m_itemTexts)
        {
            target.draw(text, states);
        }
    }

} // namespace castlecrawl
