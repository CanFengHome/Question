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
#define THRNUM (RIGHT-LEFT+1)

bool isPrime(int num);
void* work(void* arg);

typedef struct _Data
{
    pthread_t tid;
    int num;
} Data;

int main()
{
    std::vector<Data> rgData(THRNUM);
    for (int i = LEFT; i <= RIGHT; i++)
    {
        Data& data = rgData[i-LEFT];
        data.num = i;
        data.tid = 0;
        if (pthread_create(&data.tid, NULL, work, &data) != 0)
        {
            fprintf(stderr, "%s %s\n", "pthread_creat", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < (int)rgData.size(); i++)
    {
        pthread_join(rgData[i].tid, NULL);
    }
    
    return 0;
}

void* work(void* arg)
{
    Data* pData = static_cast<Data*>(arg);
    if (isPrime(pData->num))
    {
        printf("%lu %d\n", pData->tid, pData->num);
    }
    pthread_exit(NULL);
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