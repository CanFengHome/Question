#ifndef PROTO_H_
#define PROTO_H_

#include <string>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PORT 8899

#define NAMESIZE 11
struct msg_st
{
    uint8_t name[NAMESIZE];
    uint32_t math;
    uint32_t chinese;
} __attribute__((packed));

void err_exit(const char* err)
{
    perror(err);
    exit(EXIT_FAILURE);
}

#endif