#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <pthread.h>

#define EMPTY_NUM 3
#define CAR_NUM 6

struct Data
{
    int* pEmptyNum;
    int index;
    pthread_t tid;

    pthread_mutex_t* pMutex;
    pthread_cond_t* pcond;
};

void* work(void* arg);

int main()
{
    int nEmpty = EMPTY_NUM;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

    std::vector<Data> rgData(CAR_NUM);
    for (int i = 0; i < CAR_NUM; i++)
    {
        Data& data = rgData[i];
        data.pEmptyNum = & nEmpty;
        data.index = i;
        data.pMutex = &mutex;
        data.pcond = &cond;

        if (pthread_create(&data.tid, NULL, work, &data) != 0)
        {
            fprintf(stderr, "%s %s", "pthread create", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    
    for (auto& item : rgData)
    {
        pthread_join(item.tid, NULL);
    }

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    printf("now empty num: %d\n", nEmpty);

    return 0;
}

void* work(void* arg)
{
    Data* pData = static_cast<Data*>(arg);

    pthread_mutex_lock(pData->pMutex);
    while (*(pData->pEmptyNum) == 0) {
        printf("%lu %d wait for parking\n", pData->tid, pData->index);
        pthread_cond_wait(pData->pcond, pData->pMutex);
    }

    --(*pData->pEmptyNum);
    printf("%lu %d in.\n", pData->tid, pData->index);
    pthread_mutex_unlock(pData->pMutex);

    sleep(rand() % 3 + 1);
    pthread_mutex_lock(pData->pMutex);

    ++(*pData->pEmptyNum);
    printf("%lu %d out.\n", pData->tid, pData->index);
    pthread_cond_broadcast(pData->pcond);

    pthread_mutex_unlock(pData->pMutex);

    pthread_exit(NULL);
}