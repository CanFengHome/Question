#include "TokenBucket.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <vector>

#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

namespace TokenBucket
{
    // 仅考虑一秒变一次的情况，不考虑支持时间间隔的设定
    typedef struct _Bucket
    {
        int index;
        int cps;  // 流速，外部设定后不可变
        int burst; // max token上限，外部设定不可变

        int token; // 随alrm信号不断变更
    } Bucket;

    static std::vector<Bucket> g_rgBucket;

    struct sigaction oldSigAct;
    struct itimerval oldTimerval;

    void sig_alrm(int s);
    void uninit();
    bool init()
    {
        struct sigaction action;
        action.sa_flags = 0;
        sigemptyset(&action.sa_mask);
        action.sa_handler = sig_alrm;
        if (sigaction(SIGALRM, &action, &oldSigAct) < 0)
        {
            perror("sigaction.");
            exit(EXIT_FAILURE);
        }

        struct itimerval tval;
        tval.it_interval.tv_sec = 1;
        tval.it_interval.tv_usec = 0;

        tval.it_value.tv_sec = 1;
        tval.it_value.tv_usec = 0;

        setitimer(ITIMER_REAL, &tval, &oldTimerval);

        atexit(uninit);
        return true;
    }

    int createBucket(int cps, int burst)
    {
        Bucket bkt {
            .index = (int)g_rgBucket.size(),
            .cps = cps,
            .burst = burst,
            .token = 0
        };
        g_rgBucket.push_back(bkt);
        return bkt.index;
    }

    void destroyBucket(int bkt)
    {
        std::vector<Bucket>::iterator pos = g_rgBucket.begin();
        std::advance(pos, bkt);
        g_rgBucket.erase(pos);
    }

    int fetchToken(int bkt)
    {
        int ret = 0;
        while ((ret = g_rgBucket[bkt].token) <= 0)
            pause();
        g_rgBucket[bkt].token = 0;
        return ret;
    }

    void returnToken(int bkt, int retval)
    {
        g_rgBucket[bkt].token += retval;
    }

    void sig_alrm(int s)
    {
        for (auto& item : g_rgBucket)
        {
            item.token = std::min(item.burst, item.token + item.cps);
        }
    }

    void uninit()
    {
        sigaction(SIGALRM, &oldSigAct, NULL);
        setitimer(ITIMER_REAL, &oldTimerval, NULL);
    }
}