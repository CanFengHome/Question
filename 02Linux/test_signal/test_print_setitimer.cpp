#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>

#define FILE "test_print_setitimer.cpp"
#define BUF_SIZE 10
#define TIME_INTERVAL 1

void err_exit(const char* err);
int openfile(const char* file);
void rwcontent(int fd);

bool loop = true;
void sign_alrm(int s);
void setupTimer();

int main()
{
    signal(SIGALRM, sign_alrm);
    
    int fd = openfile(FILE);
    setupTimer();
    rwcontent(fd);

    return 0;
}

void err_exit(const char* err)
{
    perror(err);
    exit(EXIT_FAILURE);
}

int openfile(const char* file)
{
    int ret = open(file, O_RDONLY);
    if (ret < 0)
        err_exit("open");
    return ret;
}

void writen(int fd, const char* buf, int len);

void rwcontent(int fd)
{
    ssize_t rn = 0;
    char buf[BUF_SIZE];
    while (true)
    {
        loop = false;
        while(!loop)
            pause();

        rn = read(fd, buf, BUF_SIZE);
        if (rn == 0)
            break;
        else if (rn < 0)
        {
            if (errno == EINTR)
                continue;
            else
                err_exit("read");
        }

        writen(STDOUT_FILENO, buf, rn);
    }
}

void writen(int fd, const char* buf, int len)
{
    const char* ptr = buf;
    int left = len;

    while (left > 0) {
        int wn = write(fd, ptr, left);
        if (wn < 0)
        {
            if (errno == EINTR)
                continue;
            else
                err_exit("write");
        }
        else
        {
            ptr += wn;
            left -= wn;
        }
    }
}

void sign_alrm(int s)
{
    loop = true;
}

void setupTimer()
{
    struct itimerval tval;
    tval.it_interval.tv_sec = 1;
    tval.it_interval.tv_usec = 0;

    tval.it_value.tv_sec = 1;
    tval.it_value.tv_usec = 0;

    setitimer(ITIMER_REAL, &tval, NULL);
}