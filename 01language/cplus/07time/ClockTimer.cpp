#include "ClockTimer.hpp"

using namespace std;


ClockTimer::ClockTimer()
{
    start();
}
    
void ClockTimer::start()
{
    m_begin = chrono::system_clock::now();
}
    
double ClockTimer::elapseSeconds() const
{
    std::chrono::system_clock::time_point end = chrono::system_clock::now();
    std::chrono::duration<double> diff = end - m_begin;
    return diff.count();
}

double ClockTimer::elapseNanoseconds() const
{
    std::chrono::system_clock::time_point end = chrono::system_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_begin);
    return diff.count();
}
