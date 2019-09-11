//
//  main.cpp
//  Test
//
//  Created by mfp on 2019/9/3.
//  Copyright © 2019 ccf. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <chrono>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <array>

#include "Log.hpp"
#include "Server.hpp"
#include "Config.hpp"
#include "Client.hpp"
#include "EpollEvent.hpp"

using namespace std;

std::string request(int fd)
{
    array<char, BUFSIZ> buf;
    buf.fill('\0');
    if (recv(fd, buf.data(), buf.size(), 0) < 0)
    {
        Log::errExit("recv");
    }
    return buf.data();
}

void response(int fd, const string& data)
{
    string http_data = "HTTP/1.1 200 OK\r\nServer: loong\r\nContent-type: text/html\r\n\r\n" + data;
    if (send(fd, http_data.data(), http_data.size(), 0) < 0)
    {
        Log::errExit("send");
    }
}

int main()
{
    Log::init();
    Server server;
    server.init(PORT);

    EpollEvent event;
    event.addEvent(server.getSocket(), EPOLLIN);

    string httpText;
    while (true)
    {
        struct epoll_event item = event.next(-1);
        if (item.data.fd == server.getSocket())
        {
            Client client = server.accept();
            event.addEvent(client.getSocket(), EPOLLIN);
            cout << client.getInfo() << endl;
        }
        else if (item.events & EPOLLIN)
        {
            httpText = request(item.data.fd);
            event.modifyEvent(item.data.fd, EPOLLOUT);
        }
        else if (item.events & EPOLLOUT)
        {
            response(item.data.fd, httpText);
            event.deleteEvent(item.data.fd);
            close(item.data.fd);
        }
        else
        {
            Log::errExit("main loop");
        }
    }

    event.destroy();
    server.destroy();
    
    return 0;
}
