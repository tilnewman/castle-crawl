// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-pause.cpp
//
#include "state/state-pause.hpp"

#include "audio/music-player.hpp"
#include "audio/sound-player.hpp"
#include "display/layout.hpp"
#include "display/media.hpp"
#include "misc/context.hpp"
#include "misc/sfml-util.hpp"
#include "state/state-machine.hpp"

namespace castlecrawl
{
    StatePause::StatePause(Context & context)
        : StatePlay(context)
        , m_text()
        , m_bgFadeVerts()
    {}

    void StatePause::onEnter(Context & context)
    {
        context.music.pauseAll();
        context.audio.play("pause.ogg");

        // setup fade out the background and draw a center bar
        m_bgFadeVerts.clear();
        util::appendQuadVerts(
            context.layout.windowBounds(), m_bgFadeVerts, sf::Color(0, 0, 0, 100));

        const sf::Vector2f windowSize{ context.layout.windowSize() };
        const float centerBarheight{ windowSize.y * 0.06f };

        const sf::FloatRect centerBarRect{ { 0.0f,
                                             ((windowSize.y * 0.5f) - (centerBarheight * 0.5f)) },
                                           { windowSize.x, centerBarheight } };

        util::appendQuadVerts(centerBarRect, m_bgFadeVerts, sf::Color(0, 0, 0, 175));

        // setup the "PAUSE" text for display
        m_text.setCharacterSize(99);
        m_text.setFillColor(sf::Color(150, 150, 150));
        m_text.setFont(context.media.font());
        m_text.setString("PAUSE");

        const float textHeight{ windowSize.y * 0.1f };

        const sf::FloatRect textRect{ { 0.0f, ((windowSize.y * 0.5f) - (textHeight * 0.5f)) },
                                      { windowSize.x, textHeight } };

        util::setOriginToPosition(m_text);
        util::fitAndCenterInside(m_text, textRect);
    }

    void StatePause::onExit(Context & context) { context.music.pauseAll(); }

    void StatePause::handleEvent(Context & context, const sf::Event & event)
    {
        if ((sf::Event::KeyPressed == event.type) || (sf::Event::MouseButtonPressed == event.type))
        {
            context.audio.play("pause.ogg");
            context.state.setChangePendingToFallback();
            return;
        }
    }

    void StatePause::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        StatePlay::draw(context, target, states);
        target.draw(&m_bgFadeVerts[0], m_bgFadeVerts.size(), sf::PrimitiveType::Quads, states);
        target.draw(m_text, states);
    }

} // namespace castlecrawl
