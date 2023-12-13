#ifndef PLATFORM_HPP_INCLUDED
#define PLATFORM_HPP_INCLUDED
//
// platform.hpp
//
#include <string_view>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(WIN64) || \
    defined(_WIN64) || defined(__WINDOWS__)
#define PLATFORM_DETECTED_WINDOWS
#elif defined(macintosh) || defined(Macintosh)
#define PLATFORM_DETECTED_APPLE9
#elif defined(__APPLE__) || defined(__MACH__)
#define PLATFORM_DETECTED_APPLE
#elif defined(linux) || defined(__linux) || defined(__linux__)
#define PLATFORM_DETECTED_LINUX
#endif

#if defined(__unix) || defined(__unix__)
#define PLATFORM_DETECTED_UNIX
#endif

#if defined(__posix) || defined(__posix__)
#define PLATFORM_DETECTED_POSIX
#endif

#if defined(__CYGWIN__)
#define PLATFORM_DETECTED_CYGWIN
#endif

#if defined(__gnu_linux__)
#define PLATFORM_DETECTED_LINUX_GNU
#endif

namespace util
{

    enum class Platforms
    {
        Windows,
        Linux,
        LinuxGnu,
        Unix,
        Posix,
        Cygwin,
        Apple,
        Apple9,
        Unknown
    };

    inline constexpr std::string_view toString(const Platforms platform) noexcept
    {
        // clang-format off
        switch (platform)
        {
            case Platforms::Windows:     { return "Windows"; }
            case Platforms::Linux:       { return "Linux"; }
            case Platforms::LinuxGnu:    { return "LinuxGnu"; }
            case Platforms::Unix:        { return "Unix"; }
            case Platforms::Posix:       { return "Posix"; }
            case Platforms::Cygwin:      { return "Cygwin"; }
            case Platforms::Apple:       { return "Apple"; }
            case Platforms::Apple9:      { return "Apple9"; }
            case Platforms::Unknown:
            default:                     { return "Unknown"; }
        }
        // clang-format on
    }

    //

    class Platform
    {
      public:
        Platform();

        Platforms which() const { return m_platform; }
        bool isWindows() const { return (Platforms::Windows == m_platform); }
        bool isLinux() const { return (Platforms::Linux == m_platform); }
        bool isMacOS() const { return (Platforms::Apple == m_platform); }
        bool isSupported() const { return (isWindows() || isLinux() || isMacOS()); }

      private:
        Platforms m_platform;
    };

} // namespace util

#endif // PLATFORM_HPP_INCLUDED
