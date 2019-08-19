#include <stdio.h>
#include <string.h>

int main()
{
    char str[] = "/home/a:/home/b:/home/c";

    char* token = NULL;
    char* src = str;

    while ((token = strsep(&src, ":")) != NULL)
    {
        puts(token);
    }

    puts("end");
    puts(str);

    return 0;
}