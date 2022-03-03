// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// shaker.cpp
//
#include "shaker.hpp"

#include "check-macros.hpp"

namespace castlecrawl
{

    Shaker::Shaker()
        : m_time(0.0f)
        , m_adjustment(0.0f)
    {}

    void Shaker::update(const float frameTimeSec)
    {
        m_time += (frameTimeSec * 50.0f);
        m_adjustment = (sin(m_time) * 2.0f);

        if (m_time > 100000.0f)
        {
            m_time = 0.0f;
        }
    }

} // namespace castlecrawl
