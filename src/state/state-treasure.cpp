// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-treasure.cpp
//
#include "state/state-treasure.hpp"

#include "audio/sound-player.hpp"
#include "display/layout.hpp"
#include "display/media.hpp"
#include "display/popup-manager.hpp"
#include "misc/check-macros.hpp"
#include "misc/context.hpp"
#include "misc/player.hpp"
#include "misc/sfml-util.hpp"
#include "state/state-machine.hpp"

namespace castlecrawl
{
    StateTreasure::StateTreasure(Context & context)
        : StatePlay(context)
        , m_bgFadeVerts()
        , m_titleText()
        , m_goldText()
        , m_itemTexts()
        , m_bgRectangle()
        , m_selectIndex(0)
        , m_doneText()
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
        const FontExtent fontExtent = context.media.fontExtent(FontSize::Medium);
        float textWidest{ 0.0f };
        float itemTextPosY{ util::bottom(m_goldText) + vertPad };
        for (const item::Item & item : treasure.items)
        {
            sf::Text & text =
                m_itemTexts.emplace_back(context.media.makeText(FontSize::Medium, item.name()));

            text.setPosition(
                ((context.layout.windowSize().x * 0.5f) - (text.getGlobalBounds().width * 0.5f)),
                itemTextPosY);

            itemTextPosY += fontExtent.letter_size.y;

            if (text.getGlobalBounds().width > textWidest)
            {
                textWidest = text.getGlobalBounds().width;
            }
        }

        // done text
        if (treasure.items.empty())
        {
            m_doneText = context.media.makeText(FontSize::Small, "(press Enter to exit)");
        }
        else
        {
            m_doneText = context.media.makeText(FontSize::Medium, "(Exit)");
        }

        m_doneText.setPosition(
            ((context.layout.windowSize().x * 0.5f) - (m_doneText.getGlobalBounds().width * 0.5f)),
            (itemTextPosY + (vertPad * 1.5f)));

        // finish the cyan blusih bar
        const float bgRectangleHeight{
            (util::bottom(m_doneText) - m_bgRectangle.getGlobalBounds().top) + vertPad
        };

        m_bgRectangle.setSize(sf::Vector2f{ context.layout.windowSize().x, bgRectangleHeight });

        // selection highlight rectangle
        if (m_itemTexts.empty())
        {
            m_selectRectangle.setFillColor(sf::Color::Transparent);
        }
        else
        {
            m_selectRectangle.setFillColor(sf::Color(0, 0, 0, 64));
            m_selectRectangle.setOutlineThickness(0.0f);
            m_selectRectangle.setSize({ textWidest, fontExtent.letter_size.y });

            m_selectRectangle.setPosition(
                ((context.layout.windowSize().x * 0.5f) -
                 (m_selectRectangle.getGlobalBounds().width * 0.5f)),
                m_itemTexts[0].getGlobalBounds().top);
        }
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
            context.audio.play("thock-3.ogg");
            context.state.setChangePending(State::Play);
            return;
        }

        if (sf::Keyboard::Enter == event.key.code)
        {
            if (m_itemTexts.empty() || (m_selectIndex == m_itemTexts.size()))
            {
                context.audio.play("thock-3.ogg");
                context.state.setChangePending(State::Play);
            }
            else if (m_selectIndex < m_itemTexts.size())
            {
                context.audio.play("thud-1.ogg", 1.25f);

                const auto itemIter =
                    (std::begin(treasure.items) + static_cast<std::ptrdiff_t>(m_selectIndex));

                context.player.inventory().add(*itemIter);

                treasure.items.erase(itemIter);

                redraw(context);
            }

            return;
        }

        if ((sf::Keyboard::Up == event.key.code) && !m_itemTexts.empty())
        {
            if (m_selectIndex > 0)
            {
                context.audio.play("tick-off-1.ogg");
                --m_selectIndex;
                redraw(context);
                return;
            }
        }

        if (((sf::Keyboard::Down == event.key.code) || (sf::Keyboard::Space == event.key.code)) &&
            !m_itemTexts.empty())
        {
            if (m_selectIndex < m_itemTexts.size())
            {
                context.audio.play("tick-off-1.ogg");
                ++m_selectIndex;
                redraw(context);
                return;
            }
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
        target.draw(m_selectRectangle, states);
        target.draw(m_doneText, states);

        for (const sf::Text & text : m_itemTexts)
        {
            target.draw(text, states);
        }
    }

    void StateTreasure::redraw(Context & context)
    {
        const float vertPad{ context.layout.windowSize().y * 0.015f };

        m_itemTexts.clear();

        if (treasure.items.empty())
        {
            m_selectRectangle.setPosition(
                ((context.layout.windowSize().x * 0.5f) -
                 (m_selectRectangle.getGlobalBounds().width * 0.5f)),
                m_doneText.getGlobalBounds().top);

            return;
        }

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

        if (m_selectIndex < treasure.items.size())
        {
            m_selectRectangle.setPosition(
                ((context.layout.windowSize().x * 0.5f) -
                 (m_selectRectangle.getGlobalBounds().width * 0.5f)),
                m_itemTexts.at(m_selectIndex).getGlobalBounds().top);
        }
        else
        {
            m_selectRectangle.setPosition(
                ((context.layout.windowSize().x * 0.5f) -
                 (m_selectRectangle.getGlobalBounds().width * 0.5f)),
                m_doneText.getGlobalBounds().top);
        }
    }

} // namespace castlecrawl
