#ifndef CASTLECRAWL_GAME_HPP_INCLUDED
#define CASTLECRAWL_GAME_HPP_INCLUDED
//
// game.hpp
//
namespace castlecrawl
{

    // All info about a game in progress that can changes during play.
    class GameInPlay
    {
      public:
        GameInPlay() = default;

        void setup()
        {
            m_isGameOver = false;
            m_didPlayerWin = false;
        }

        bool isGameOver() const { return m_isGameOver; }

        void endGame(const bool didPlayerWin)
        {
            m_isGameOver = true;
            m_didPlayerWin = didPlayerWin;
        }

        bool didPlayerWin() const
        {
            if (!m_isGameOver)
            {
                return false;
            }

            return m_didPlayerWin;
        }

      protected:
        bool m_isGameOver{ false };
        bool m_didPlayerWin{ false };
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_GAME_HPP_INCLUDED
