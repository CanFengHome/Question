#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0)
        err_exit("socket");
    
    struct sockaddr_in laddr;
    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr.s_addr);
    if (bind(sd, (struct sockaddr*)&laddr, sizeof(laddr)) < 0)
        err_exit("bind");
    
    struct sockaddr_in raddr;
    socklen_t addrlen = sizeof(raddr);
    msg_st buf;
    char ipstr[32];
    while (true)
    {
        ssize_t len = recvfrom(sd, &buf, sizeof(buf), 0, (struct sockaddr*)&raddr, &addrlen);
        if (len < 0) {
            err_exit("recvfrom");
        }
        
        printf("---message from %s:%d---\n",
            inet_ntop(AF_INET, &raddr.sin_addr.s_addr, ipstr, sizeof(ipstr)),
            ntohs(raddr.sin_port));
        printf("NAME=%s MATH=%d CHINESE=%d \n", buf.name, ntohl(buf.math), ntohl(buf.chinese));
    }
    
    close(sd);

    return 0;
}



