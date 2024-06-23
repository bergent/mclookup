#ifndef __H_CORE_EVLOOP__
#define __H_CORE_EVLOOP__

#include "network/socket.h"
#include "sys/epoll.h"

#include <deque>
#include <memory>

namespace mccore {

class EventLoop {
public:
    EventLoop() = default;
    EventLoop(int num_fds);

    int run();
    const epoll_event* events() const;

    bool track(int fd);
    bool track(std::deque<mcnet::Socket>& sockets);

    bool untrack(int fd);

    int fd() const;

private:
    std::unique_ptr<epoll_event> _events {};
    int _num_fds;
    int _epoll_fd;
};

};


#endif
