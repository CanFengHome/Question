#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <pthread.h>

#define THRNUM 10
#define LOOP 10
int num = 0;

void cal();
void* work(void* arg);
struct Data
{
    pthread_t tid;
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
    std::vector<Data> rgData(THRNUM);

    for (size_t i = 0; i < THRNUM; i++)
    {
        if (pthread_create(&rgData[i].tid, NULL, work, &rgData[i]) != 0)
        {
            // ..
            exit(EXIT_FAILURE);
        }
    }

    for (size_t i = 0; i < THRNUM; i++)
    {
        pthread_join(rgData[i].tid, NULL);
    }

    pthread_mutex_destroy(&mutex);

    std::cout << num << std::endl;

    return 0;
}

void* work(void* arg)
{
    cal();

    pthread_exit(NULL);
}

void cal()
{
    for (size_t i = 0; i < LOOP; i++)
    {
        pthread_mutex_lock(&mutex);
        ++num;
        pthread_mutex_unlock(&mutex);
        usleep(10000);
    }
}

