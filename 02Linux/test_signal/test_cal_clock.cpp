#include <iostream>
#include <chrono>

using namespace std;

class ClockTimer
{
public:
    void start()
    {
        m_begin = std::chrono::system_clock::now();
    }
    
    double elapseSeconds()
    {
        std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end - m_begin;
        return diff.count();
    }
    
private:
    std::chrono::system_clock::time_point m_begin;
};


int main()
{
    ClockTimer timer;
    int64_t num = 0;

    timer.start();
    while (timer.elapseSeconds() <= 5.0)
    {
        ++num;
    }
    
    std::cout << num << std::endl;
    
    return 0;
}
