#include <stdio.h>
#include <stdarg.h>

#include <iostream>
#include <string>

using namespace std;

void err_exit(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);

    char buf[BUFSIZ];
    vsnprintf(buf, BUFSIZ, format, ap);
    fprintf(stderr, "Error:%s", buf);

    va_end(ap);

    exit(EXIT_FAILURE);
}

int main()
{
    err_exit("test printf info %d\n", 100);

    return 0;
}