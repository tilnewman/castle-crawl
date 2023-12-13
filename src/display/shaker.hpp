#ifndef CASTLECRAWL_SHAKER_HPP_INCLUDED
#define CASTLECRAWL_SHAKER_HPP_INCLUDED
//
// shaker.hpp
//
namespace castlecrawl
{

    class Shaker
    {
      public:
        Shaker();

        void update(const float frameTimeSec);
        float adjustment() const { return m_adjustment; }

      private:
        float m_time;
        float m_adjustment;
    };

} // namespace castlecrawl

#endif // CASTLECRAWL_SHAKER_HPP_INCLUDED
