#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "common.hpp"

enum EState
{
    SM_R,
    SM_W,
    SM_EX,
    SM_T
};

struct StateMache
{
    EState state;
    int rdfd;
    int wdfd;

    char buf[BUFSIZ];
    int rdLen;
    int wdpos;
};

void relay(int readfd, int writefd);
void drive(StateMache* mache);

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "cmd format: ./cmd tty|fifo\n");
        exit(EXIT_FAILURE);
    }

    std::string rdfile;
    std::string wdfile;
    if (strcmp("tty", argv[1]) == 0)
    {
        rdfile = "/dev/tty";
        wdfile = FIFOFILE;
        mkFifo(wdfile);
    }
    else
    {
        rdfile = FIFOFILE;;
        wdfile = "/dev/tty";
        mkFifo(wdfile);
    }

    int readfd = open(rdfile.c_str(), O_RDONLY);
    if (readfd < 0)
        err_exit("open read");

    int writefd = open(wdfile.c_str(), O_WRONLY);
    if (writefd < 0)
        err_exit("open write");

    relay(readfd, writefd);
    
    close(writefd);
    close(readfd);
    puts("==== all ok. ====");

    return 0;
}

void relay(int readfd, int writefd)
{
    int readfd_save = fcntl(readfd, F_GETFL);
    fcntl(readfd, readfd_save | O_NONBLOCK);
    int writefd_save = fcntl(writefd, F_GETFL);
    fcntl(writefd, writefd_save | O_NONBLOCK);

    StateMache mache;
    mache.state = SM_R;
    mache.rdfd = readfd;
    mache.wdfd = writefd;
    mache.rdLen = 0;
    mache.wdpos = 0;

    while (mache.state != SM_T)
    {
        drive(&mache);
    }

    fcntl(readfd, readfd_save);
    fcntl(writefd, writefd_save);

    close(readfd);
    close(writefd);
}

void drive(StateMache* mache)
{
    switch (mache->state)
    {
    case SM_R:
    {
        mache->rdLen = read(mache->rdfd, mache->buf, BUFSIZ);
        if (mache->rdLen == 0)
        {
            mache->state = SM_T;
        }
        else if (mache->rdLen < 0)
        {
            if (errno == EAGAIN) {
                mache->state = SM_R;
            } else {
                mache->state = SM_EX;
            }
        }
        else
        {
            mache->wdpos = 0;
            mache->state = SM_W;
        }
        
    }
        break;
    case SM_W:
    {
        int wdlen = write(mache->wdfd, mache->buf + mache->wdpos, mache->rdLen);
        if (wdlen < 0)
        {
            if (errno == EAGAIN)
            {
                mache->state = SM_W;
            }
            else
            {
                mache->state = SM_EX;
            }
        }
        else
        {
            mache->wdpos += wdlen;
            mache->rdLen -= wdlen;
            if (mache->rdLen == 0)
            {
                mache->state = SM_R;
            }
            else
            {
                mache->state = SM_W;
            }
            
        }
    }
        break;
    case SM_EX:
    {
        perror("sm_ex");
        mache->state = SM_T;
    }
        break;
    case SM_T:
    {
        // do someting
    }
        break;
    default:
        abort();
        break;
    }
}