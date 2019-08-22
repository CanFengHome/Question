#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>

void sig_int(int s)
{
    write(STDOUT_FILENO, "!", 1);
}

int main()
{
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = sig_int;
    if (sigaction(SIGINT, &act, NULL) < 0)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    sigset_t set, saveset;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    sigprocmask(SIG_UNBLOCK, &set, &saveset);

    sigset_t oldset;
    sigprocmask(SIG_BLOCK, &set, &oldset);

    for (size_t i = 0; i < 1000; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            write(STDOUT_FILENO, "*", 1);
            sleep(1);
        }
        write(STDOUT_FILENO, "\n", 1);
        sigsuspend(&oldset);
        /*
            sigset_t tmpset;
            sigprocmask(SIG_SETMASK, &oldset, &tmpset);
            pause();
            sigprocmask(SIG_SETMASK, &tmpset, NULL);
        */
    }
    sigprocmask(SIG_SETMASK, &saveset, NULL);

    return 0;
}