#ifndef __H_CORE_SCHEDULER__
#define __H_CORE_SCHEDULER__

#include "core/worker.h"
#include "network/ip.h"

#include <vector>

namespace mccore {

class Scheduler {
public:
    Scheduler() = delete;
    Scheduler(const mcnet::DynamicAddress& work, size_t num_workers);

    int run();

private:
    mcnet::DynamicAddress _work;

    size_t _num_workers;
    uint32_t _socket_capacity {1000};

    std::vector<Worker> _workers;
    WorkerOptions _worker_options;
};

};


#endif
