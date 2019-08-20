#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

void err_exit(const char* err);
int getFileSize(const char* file);
int openFile(const char* file);
int createFile(const char* file, off_t length);

typedef struct _Data
{
    char* ptrSrc;
    char* ptrDest;
    int len;
} Data;

void child_work(const Data& data);

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cout << "format: ./cmd srcfile destfile" << std::endl;
        exit(EXIT_FAILURE);
    }

    int size = getFileSize(argv[1]);
    int srcfd = openFile(argv[1]);
    int destfd = createFile(argv[2], size);

    char* ptrSrc = (char*)mmap(NULL, size, PROT_READ, MAP_SHARED, srcfd, 0);
    if (ptrSrc == MAP_FAILED)
        err_exit("mmap src");

    char* ptrDest = (char*)mmap(NULL, size, PROT_WRITE, MAP_SHARED, destfd, 0);
    if (ptrDest == MAP_FAILED)
        err_exit("mmap dest");

    const int process_num = 10;
    const int process_step = process_num / size;

    for (int i=0; i<process_num; ++i)
    {
        pid_t pid = fork();
        if (pid < 0)
            err_exit("fork");

        if (pid == 0)
        {
            Data data;
            data.ptrDest = ptrDest + (i * process_step);
            data.ptrSrc = ptrSrc + (i * process_step);
            data.len = process_step;
            if (i == (process_num - 1))
            {
                data.len = size - (process_num-1) * process_step;
            }

            child_work(data);
            exit(EXIT_SUCCESS);
        }
    }

    for (int i=0; i<process_num; ++i)
    {
        wait(NULL);
    }

    munmap(ptrDest, size);
    munmap(ptrSrc, size);

    return 0;
}

void err_exit(const char* err)
{
    perror(err);
    exit(EXIT_FAILURE);
}

int getFileSize(const char* file)
{
    struct stat statbuf;
    if (stat(file, &statbuf) < 0) {
        err_exit("stat");
    }

    return statbuf.st_size;
}

int openFile(const char* file)
{
    int ret = open(file, O_RDONLY);
    if (ret < 0) {
        err_exit("open readonly");
    }
    return ret;
}

int createFile(const char* file, off_t length)
{
    // 因为mmap需要必须具有read权限，所以这里用了可读可写
    int ret = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (ret < 0) {
        err_exit("open write");
    }

    if (ftruncate(ret, length) < 0)
    {
        err_exit("ftruncate");
    }

    return ret;
}

void child_work(const Data& data)
{
    char* psrc = data.ptrSrc;
    char* pdest = data.ptrDest;
    int len = data.len;

    while (len > 0)
    {
        *pdest++ = *psrc++;
        --len;
    }
}