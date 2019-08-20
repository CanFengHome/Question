#include <iostream>
#include <string>

#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void err_exit(const char* err)
{
    perror(err);
    exit(EXIT_FAILURE);
}

void child_work(int rfd);

int main()
{
    int fds[2];
    if (pipe(fds) < 0)
    {
        err_exit("pipe");
    }
    pthread_t pid = fork();
    if (pid < 0)
    {
        err_exit("fork");
    }
    else if (pid == 0)
    {
        close(fds[1]);
        child_work(fds[0]);
        close(fds[0]);
        exit(0);
    }
    else
    {
        close(fds[0]);
        string msg("hello");
        cout << getpid() << " write data. " << endl;
        if (write(fds[1], msg.c_str(), msg.size()) < 0)
        {
            err_exit("write");
        }
        wait(NULL);
        close(fds[1]);
    }   

    return 0;
}

void child_work(int rfd)
{
    char buf[BUFSIZ]={0};
    read(rfd, buf, BUFSIZ);
    cout << getpid() << " receive: " << buf << endl;
}