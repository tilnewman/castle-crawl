// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// summoner.cpp
//
#include "map/summoner.hpp"

#include "map/board.hpp"
#include "misc/context.hpp"
#include "misc/sfml-util.hpp"

#include <algorithm>

namespace castlecrawl
{

    Summoners::Summoners()
        : m_summoners()
    {}

    void Summoners::update(Context & context, const float frameTimeSec)
    {
        for (SummonerInstance & instance : m_summoners)
        {
            instance.timer_sec -= frameTimeSec;
            if (instance.timer_sec < 0.0f)
            {
                instance.timer_sec = summonRateSec(instance.summoner);
                summon(context);
            }
        }
    }

    void Summoners::add(Context & context, const SummonerInstance & si)
    {
        m_summoners.push_back(si);

        context.board.add(
            Piece(context, piece(si.summoner), tileImageChar(tileImage(si.summoner)), si.position));
    }

    void Summoners::remove(Context & context, const MapPos_t & pos)
    {
        m_summoners.erase(
            std::remove_if(
                std::begin(m_summoners),
                std::end(m_summoners),
                [&](const SummonerInstance & si) { return (si.position == pos); }),
            std::end(m_summoners));

        context.board.remove(pos);
    }

    void Summoners::summon(Context &) {}

} // namespace castlecrawl
