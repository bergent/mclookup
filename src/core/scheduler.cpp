#include "core/scheduler.h"
#include <iostream>

namespace mccore {

Scheduler::Scheduler(const mcnet::DynamicAddress& work, size_t num_workers) 
    : _work {work}, _num_workers {num_workers}
{
    mcnet::DAData work_data = _work.get_data();

    uint64_t total_ips = work_data.ip_finish - work_data.ip_start + 1;
    
    
    if (num_workers > total_ips) {
        num_workers = total_ips;
    }

    uint64_t leftover_ips {0};

    while (total_ips % num_workers != 0) {
        total_ips--;
        leftover_ips++;
    }
    _worker_options.amount_of_work = total_ips / num_workers;
    _worker_options.data = work_data;
    
    
    while (_socket_capacity % num_workers != 0) {
        _socket_capacity--;
    }
    _worker_options.num_sockets = _socket_capacity / num_workers;
    
     
    for (size_t idx {0}; idx < num_workers; ++idx) {
        if (idx == num_workers - 1) {
            _worker_options.data.ip_finish = _worker_options.data.ip_start + 
                                             _worker_options.amount_of_work + leftover_ips - 1;
            auto& worker = _workers.emplace_back(_worker_options);
            worker.setup();
        }
        else {
            _worker_options.data.ip_finish = _worker_options.data.ip_start + _worker_options.amount_of_work - 1;
            auto& worker = _workers.emplace_back(_worker_options);
            worker.setup();
            _worker_options.data.ip_start = _worker_options.data.ip_finish + 1;

        }
    }
    
}

int 
Scheduler::run() {
    for (auto& worker : _workers) {
        worker.work();
    }
    return 0;
}
    

};
