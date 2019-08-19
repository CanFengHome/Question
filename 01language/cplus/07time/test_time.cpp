#include <time.h>
#include <iostream>
#include <string>

using namespace std;

#define FULL_FMT "%F %T"
#define DAY_FMT "%F"
#define CLOCK_FMT "%T"

string getCurTime(const string format)
{
    time_t t = time(NULL);
    char buf[512]={0};
    strftime(buf, sizeof(buf)-1, format.c_str(), localtime(&t));
    return buf;
}

int main()
{
    cout << "now full format: " << getCurTime(FULL_FMT) << endl;
    cout << "now day format: " << getCurTime(DAY_FMT) << endl;
    cout << "now clock format: " << getCurTime(CLOCK_FMT) << endl;

    return 0;
}