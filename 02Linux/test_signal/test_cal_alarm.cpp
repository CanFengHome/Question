#include <iostream>
#include <unistd.h>
#include <signal.h>

bool loop = true;
void sig_alrm(int s)
{
    loop = false;
}

int main()
{
    struct sigaction action;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    action.sa_handler = sig_alrm;
    
    if (sigaction(SIGALRM, &action, NULL) < 0)
    {
        perror("sigaction.");
        exit(EXIT_FAILURE);
    }

    alarm(5);
    int64_t num = 0;
    while (loop)
    {
        ++num;
    }

    std::cout << num << std::endl;

    return 0;
}