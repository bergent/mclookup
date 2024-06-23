#include "core/evloop.h"
#include <stdexcept>
#include <sys/epoll.h>

namespace mccore {

EventLoop::EventLoop(int num_fds) 
    : _num_fds {num_fds}
{
    _epoll_fd = epoll_create1(0);
    _events.reset( new epoll_event[num_fds] );
    
}

int
EventLoop::run() {
start:
    int polled_events = epoll_wait(_epoll_fd, _events.get(), _num_fds, 10);
    
    if (polled_events < 0 and errno == EINTR) {
        goto start;
    }
    
    if (polled_events < 0 and errno != EINTR) {
        perror("");
        throw std::runtime_error("Error: Poll failed");
    }

    return polled_events;
}

bool 
EventLoop::track(int fd) {
    epoll_event event;
    event.events = EPOLLIN | EPOLLRDHUP;
    event.data.fd = fd;

    int rc = epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &event);
    if (rc < 0) {
        perror("Epoll CTL failed: ");
        throw std::runtime_error("Error in epoll_ctl()");
    }

    return true;
}

bool 
EventLoop::track(std::deque<mcnet::Socket>& sockets) {
    for (const auto& socket : sockets) {
        epoll_event event;
        event.events = EPOLLIN | EPOLLRDHUP;
        event.data.fd = socket.fd;

        int rc = epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, socket.fd, &event);
        if (rc < 0) {
            perror("Epoll CTL_ADD failed: ");
            throw std::runtime_error("Error in epoll_ctl()");
        }
    }
    return true;
}

bool 
EventLoop::untrack(int fd) {
    int rc = epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, NULL);
    if (rc < 0) {
        perror("Epoll CTL_DEL failed: ");
        throw std::runtime_error("Error in epoll_ctl()");
    }
    return true;
}

int 
EventLoop::fd() const {
    return _epoll_fd;
}

};
