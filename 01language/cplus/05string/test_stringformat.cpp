#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <string>

using namespace std;

string strFormat(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);

    char buf[BUFSIZ] = {0};
    vsnprintf(buf, sizeof(buf) - 1, format, ap);

    va_end(ap);

    return buf;
}

int main()
{
    string str = strFormat("ok, you hava open the num: %d", 3);
    cout << str << endl;

    return 0;
}