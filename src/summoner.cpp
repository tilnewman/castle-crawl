// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// summoner.cpp
//
#include "summoner.hpp"

#include "board.hpp"
#include "context.hpp"
#include "util.hpp"

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
            Piece(context, piece(si.summoner), summonImage(si.summoner), si.position));
    }

    void Summoners::remove(const MapPos_t & pos)
    {
        m_summoners.erase(
            std::remove_if(
                std::begin(m_summoners),
                std::end(m_summoners),
                [&](const SummonerInstance & si) { return (si.position == pos); }),
            std::end(m_summoners));
    }

    void Summoners::summon(Context & context) {}

} // namespace castlecrawl
