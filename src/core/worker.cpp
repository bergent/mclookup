#include "core/worker.h"
#include "iostream"
#include <cerrno>
#include <sys/epoll.h>
#include <sys/socket.h>

namespace mccore {

int Worker::static_id {0};

Worker::Worker(const WorkerOptions& options)
    : _options {options}, _evloop {options.num_sockets}
{
    _id = ++static_id;
    _work = mcnet::DynamicAddress(options.data.ip_start, options.data.ip_finish, 
                                  options.data.port_start, options.data.port_finish,
                                  options.data.human_ip, options.data.human_port);

    std::cout << "Worker #" << _id << " has " << options.num_sockets << " sockets\n";
    _sockets.resize(options.num_sockets);
}


bool 
Worker::setup() {
    if (!_evloop.track(_sockets)) {
        return false;
    }

    return true;
}

bool 
Worker::work() {
    std::cout << "Worker #" << _id << " connection procedure...\n";
    
    
connection:
    for (auto& socket : _sockets) {
        auto& addr = _work.get_addr();
        int connect_rc = connect(socket.fd, (sockaddr*)(&addr), sizeof(addr));

        if (errno == EINPROGRESS) {
            epoll_ctl(_evloop.fd(), EPOLL_CTL_MOD, EPOLLIN | EPOLLRDHUP | EPOLLOUT, NULL);
        }
        _work.next();
    }


    _is_done = true;
    return true;
}
    
};
