#ifndef __H_CORE_WORKER__
#define __H_CORE_WORKER__

#include "core/evloop.h"
#include "network/ip.h"
#include "network/socket.h"
#include <deque>

namespace mccore {

struct WorkerOptions {
    mcnet::DAData data;
    int num_sockets {0};
    uint64_t amount_of_work {0};
};

class Worker {

static int static_id;
public:
    Worker() = delete;
    Worker(const WorkerOptions& options);
    
    bool setup();
    bool work();
    bool is_done();

private:
    int _id {};
    bool _is_done {false};

    WorkerOptions _options; 
    
    EventLoop _evloop;
    mcnet::DynamicAddress _work;
    std::deque<mcnet::Socket> _sockets;
};

};

#endif
