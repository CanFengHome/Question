#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <pthread.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM 10

int g_worknum = 0;

void* work(void* arg);
void* task(void* arg);
bool isPrime(int num);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int main()
{
    pthread_t tids[THRNUM+1];
    if (pthread_create(&tids[0], NULL, task, NULL) != 0)
    {
        fprintf(stderr, "%s %s\n", "pthread_creat", strerror(errno));
        exit(EXIT_FAILURE);
    }

    std::vector<int> rgIndexs(THRNUM+1);
    for (int i = 1; i < THRNUM+1; i++)
    {
        rgIndexs[i] = i;
        if (pthread_create(&tids[i], NULL, work, &rgIndexs[i]) != 0)
        {
            fprintf(stderr, "%s %s\n", "pthread_creat", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    for (int i = THRNUM; i >=0 ; --i)
    {
        pthread_join(tids[i], NULL);
    }

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    return 0;
}

bool isPrime(int num)
{
    for (int i = 2; i < num/2; i++)
    {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void* work(void* arg)
{
    int* pIndex = static_cast<int*>(arg);

    while (true)
    {
        pthread_mutex_lock(&mutex);
        if (g_worknum < 0) 
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
        else if (g_worknum > 0)
        {
            int num = g_worknum;
            g_worknum = 0;
            pthread_mutex_unlock(&mutex);
            pthread_cond_broadcast(&cond);

            if (isPrime(num))
            {
                printf("index:%d %d\n", *pIndex, num);
            }
        }
        else if (g_worknum == 0)
        {
            while (g_worknum == 0)
                pthread_cond_wait(&cond, &mutex);
            pthread_mutex_unlock(&mutex);
        }
    }

    pthread_exit(NULL);
}

void* task(void* arg)
{
    int cur = LEFT;
    while (true)
    {
        pthread_mutex_lock(&mutex);
        if (g_worknum < 0) 
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
        else if (g_worknum == 0)
        {
            if (cur <= RIGHT)
            {
                g_worknum = cur;
                ++cur;
                pthread_cond_signal(&cond); // 激活一个处理任务 因为发任务的线程只有一个
            }
            else
            {
                g_worknum = -1;
                pthread_cond_broadcast(&cond); // 全部激活判断结束
            }
        }
        else if (g_worknum > 0)
        {
            while (g_worknum > 0)
                pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}