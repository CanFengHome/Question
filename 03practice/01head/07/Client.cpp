//
//  Client.cpp
//  Test
//
//  Created by mfp on 2019/9/11.
//  Copyright © 2019 ccf. All rights reserved.
//

#include "Client.hpp"

#include <cstring>
#include <unistd.h>

#include "Utility.hpp"

using namespace std;

Client::Client(int socket, const struct sockaddr_in* socket_addr)
: m_socket(socket)
{
    m_ip = inet_ntoa(socket_addr->sin_addr);
    m_port = ntohs(socket_addr->sin_port);
}

int Client::getSocket() const
{
    return m_socket;
}

string Client::getInfo() const
{
    return Utility::formatStr("client ip: %s, port:%d", m_ip.c_str(), m_port);
}

void Client::destroy()
{
    close(m_socket);
}