#ifndef CLOCK_TIMER_HPP_
#define CLOCK_TIMER_HPP_

#include <chrono>

class ClockTimer
{
public:
    ClockTimer();
    
    void start();
    
    double elapseSeconds() const;
    double elapseNanoseconds() const;
private:
    std::chrono::system_clock::time_point m_begin;
};

#endif