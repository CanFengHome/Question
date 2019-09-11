#include "EpollEvent.hpp"

#include <unistd.h>

#include "Log.hpp"

using namespace std;

EpollEvent::EpollEvent(int maxEvents/* = 100*/)
: m_maxEvents(maxEvents)
{
    m_epoll = epoll_create(1);
    if (m_epoll < 0)
    {
        Log::errExit("epoll_create");
    }

    m_rgEvents.resize(m_maxEvents);
    m_eventCount = 0;
    m_currIndex = 0;
}

int EpollEvent::controlEvent(int fd, int option, uint32_t events)
{
    struct epoll_event tempEvent {};
    tempEvent.data.fd = fd;
    tempEvent.events = events;
    return epoll_ctl(m_epoll, option, fd, &tempEvent);
}

int EpollEvent::addEvent(int fd, uint32_t events)
{
    return controlEvent(fd, EPOLL_CTL_ADD, events);
}

int EpollEvent::modifyEvent(int fd, uint32_t events)
{
    return controlEvent(fd, EPOLL_CTL_MOD, events);
}

int EpollEvent::deleteEvent(int fd)
{
    return controlEvent(fd, EPOLL_CTL_DEL, 0);
}

const struct epoll_event& EpollEvent::next(int timeout)
{
    if (m_currIndex >= m_eventCount)
    {
        m_eventCount = epoll_wait(m_epoll, m_rgEvents.data(), m_maxEvents, timeout);
        m_currIndex = 0;
    }

    return m_rgEvents[m_currIndex++];
}

void EpollEvent::destroy()
{
    close(m_epoll);
}