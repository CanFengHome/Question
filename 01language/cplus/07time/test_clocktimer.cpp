#include <iostream>
#include <unistd.h>

#include "ClockTimer.hpp"

using namespace std;

int main()
{
    ClockTimer timer;

    sleep(1);
    cout << "sec: " << timer.elapseSeconds() << endl;

    timer.start();
    sleep(2);
    cout << "sec: " << timer.elapseSeconds() << endl;
    cout << "nano sec: " << timer.elapseNanoseconds() << endl;

    return 0;
}