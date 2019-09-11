//
//  Server.cpp
//  Test
//
//  Created by mfp on 2019/9/11.
//  Copyright © 2019 ccf. All rights reserved.
//

#include "Server.hpp"

#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>

#include <string.h>

#include "Log.hpp"
#include "Client.hpp"

void Server::init(int port)
{
    init("0.0.0.0", port);
}

void Server::init(const std::string &host, int port)
{
    m_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (m_socket < 0)
    {
        Log::errExit("socket");
    }
    
    int allow_reuse = 1;
    setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &allow_reuse, sizeof(allow_reuse));
    
    struct sockaddr_in ad;
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = PF_INET;
    unsigned long inaddr = inet_addr(host.c_str());
    if (inaddr != INADDR_NONE)
    {
        memcpy(&ad.sin_addr, &inaddr, sizeof(inaddr));
    }
    else
    {
        // 如果转换失败，说明这是个域名地址，于是调用gethostbyname()进行DNS解析
        struct hostent *hp = gethostbyname(host.c_str());
        if (hp == NULL)
            m_socket = -1;
        memcpy(&ad.sin_addr, hp->h_addr, hp->h_length);
    }
    ad.sin_port = htons(port);
    
    if (bind(m_socket, (struct sockaddr*)&ad, sizeof(ad)) < 0)
    {
        Log::errExit("bind");
    }
    
    if (listen(m_socket, 10) < 0)
    {
        Log::errExit("listen");
    }
}

void Server::setBlock()
{
    int mode = fcntl(m_socket, F_GETFL, 0);
    if (mode < 0)
    {
        Log::errExit("setblock fcntl");
    }
    fcntl(m_socket, F_SETFL, mode & ~O_NONBLOCK);
}

void Server::setUnBlock()
{
    int mode = fcntl(m_socket, F_GETFL, 0);
    if (mode < 0)
    {
        Log::errExit("setblock fcntl");
    }
    fcntl(m_socket, F_SETFL, mode | O_NONBLOCK);
}


int Server::getSocket() const
{
    return m_socket;
}

Client Server::accept()
{
    struct sockaddr_in client_socket_addres;
    socklen_t client_socket_address_length = sizeof(client_socket_addres);
    int client_socket = ::accept(m_socket, (struct sockaddr*)&client_socket_addres, &client_socket_address_length);
    
    return Client(client_socket, &client_socket_addres);
}

void Server::destroy()
{
    close(m_socket);
    m_socket = -1;
}
