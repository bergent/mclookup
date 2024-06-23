#ifndef __H_NETWORK_IP__
#define __H_NETWORK_IP__

#include <string>
#include <cstring>
#include <cstdint>
#include <netinet/in.h>

namespace mcnet {

class DynamicAddress {
public:
    static const uint32_t MAX_IP_VAL {4294967295};
    static const uint16_t MAX_PORT_VAL {65535};

public:
    DynamicAddress();
    DynamicAddress(size_t ip_start, size_t ip_finish,
                   uint16_t port_start = 0, uint16_t port_finish = MAX_PORT_VAL);
    DynamicAddress(const std::string& ip_start, const std::string& ip_finish,
                   uint16_t port_start = 0, uint16_t port_finish = MAX_PORT_VAL);

    bool next();
    bool is_completed();
    
    std::string get_ip_str();
    uint16_t get_port() const;

    const sockaddr_in& get_addr() const; 
 
private:
    bool _human_ip {false};
    bool _human_port {false};
    bool _completed {false};

    sockaddr_in _sin {};

    uint16_t _port_start {0};
    uint16_t _port_current {0};
    uint16_t _port_finish {MAX_PORT_VAL};

    size_t _ip_start {0};
    size_t _ip_current {0};
    size_t _ip_finish {MAX_IP_VAL};
    
    char _ip_buf [INET_ADDRSTRLEN];
    socklen_t _slen {sizeof(_sin)};
};

};


#endif
