#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "proto.h"


int main()
{
    srand(time(NULL));

    int sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0)
        err_exit("socket");
    
    struct sockaddr_in raddr;
    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &raddr.sin_addr.s_addr);

    msg_st buf;
    strcpy((char*)buf.name, "hello");
    buf.math = htonl(rand() % 100);
    buf.chinese = htonl(rand() % 100);
    if (sendto(sd, &buf, sizeof(buf), 0, (struct sockaddr*)&raddr, sizeof(raddr)) < 0)
        err_exit("sendto");
    
    puts("ok!");
    close(sd);

    return 0;
}

