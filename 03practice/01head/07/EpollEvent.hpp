#ifndef EPOLL_EVENT_hpp
#define EPOLL_EVENT_hpp

#include <sys/epoll.h>

#include <vector>

class EpollEvent
{
public:
    explicit EpollEvent(int maxEvents = 100);
    EpollEvent(const EpollEvent& other) = delete;
    EpollEvent& operator=(const EpollEvent& other) = delete;

    int controlEvent(int fd, int option, uint32_t events);
    int addEvent(int fd, uint32_t events);
    int modifyEvent(int fd, uint32_t events);
    int deleteEvent(int fd);

    const struct epoll_event& next(int timeout);

    void destroy();
private:
    int m_epoll = 0;
    int m_maxEvents;


    int m_eventCount = 0;
    int m_currIndex = 0;
    std::vector<struct epoll_event> m_rgEvents;
};

#endif