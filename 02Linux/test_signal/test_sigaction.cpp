#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_int(int s)
{
    write(STDOUT_FILENO, "!", 1);
}

int main()
{
    struct sigaction action;
    action.sa_flags=0;
    sigemptyset(&action.sa_mask);
    action.sa_handler = sig_int;
    sigaction(SIGINT, &action, NULL);

    for (size_t i = 0; i < 10; i++)
    {
        write(STDOUT_FILENO, "*", 1);
        sleep(1);
    }
    
    return 0;
}