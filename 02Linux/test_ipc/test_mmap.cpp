#include <iostream>
#include <string>

#include <stdio.h>

#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

void err_exit(const char* err)
{
    perror(err);
    exit(EXIT_FAILURE);
}

void* getMalloc(size_t length)
{
    void* ret = mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    if (ret == MAP_FAILED)
        err_exit("mmap");
    return ret;
}

void freeMalloc(void* ptr, size_t length)
{
    munmap(ptr, length);
}

int main()
{
    char* buf = (char*)getMalloc(BUFSIZ);
    if (buf == NULL)
        exit(EXIT_FAILURE);

    pid_t pid = fork();
    if (pid < 0)
        err_exit("mmap");

    if (pid == 0)
    {
        std::string msg = "hello! who are you?";
        for (auto& item : msg) {
            *buf++ = item;
        }
        exit(0);
    }
    else
    {
        wait(NULL);
        std::string msg;
        char* ptr = buf;
        while (*ptr != '\0')
        {
            msg.push_back(*ptr);
            ++ptr;
        }
        std::cout << "parent receive: " << msg << std::endl;
    }

    freeMalloc(buf, BUFSIZ);

    return 0;
}