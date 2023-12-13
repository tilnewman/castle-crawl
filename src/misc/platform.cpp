// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// platform.cpp
//
#include "misc/platform.hpp"

namespace util
{

    Platform::Platform()
        : m_platform(Platforms::Unknown)
    {
#ifdef PLATFORM_DETECTED_WINDOWS
        m_platform = Platforms::Windows;
#endif

#ifdef PLATFORM_DETECTED_APPLE9
        m_platform = Platforms::Apple9;
#endif

#ifdef PLATFORM_DETECTED_APPLE
        m_platform = Platforms::Apple;
#endif

#ifdef PLATFORM_DETECTED_LINUX
        m_platform = Platforms::Linux;
#endif

#ifdef PLATFORM_DETECTED_UNIX
        m_platform = Platforms::Unix;
#endif

#ifdef PLATFORM_DETECTED_POSIX
        m_platform = Platforms::Posix;
#endif

#ifdef PLATFORM_DETECTED_CYGWIN
        m_platform = Platforms::Cygwin;
#endif

#ifdef PLATFORM_DETECTED_LINUX_GNU
        m_platform = Platforms::LinuxGnu;
#endif
    }

} // namespace util
