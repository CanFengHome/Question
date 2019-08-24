#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <string>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFOFILE "test.pipo"

bool isFileExist(const std::string& file)
{
    return access(file.c_str(), F_OK) == 0;
}

void mkFifo(const std::string& file)
{
    if (isFileExist(file))
        return;

    if (mkfifo(file.c_str(), 0666) < 0) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
}

void err_exit(const char* err)
{
    perror(err);
    exit(EXIT_FAILURE);
}

#endif