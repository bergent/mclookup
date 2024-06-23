#include "network/ip.h"
#include <arpa/inet.h>
#include <cstdint>
#include <netinet/in.h>
#include <stdexcept>

#include <iostream>

namespace mcnet {

DynamicAddress::DynamicAddress() {
    _sin.sin_family = AF_INET;
    _sin.sin_addr.s_addr = _ip_start;
    _sin.sin_port = _port_start;
}

DynamicAddress::DynamicAddress(size_t ip_start, size_t ip_finish, 
                               uint16_t port_start, uint16_t port_finish,
                               bool human_ip, bool human_port)
{
    if (port_start > port_finish) {
        throw std::range_error("Invalid port range: Start port should be less than Finish port.");
    }

    if (ip_start > ip_finish) {
        throw std::range_error("Invalid IP range: Start IP should be less then Finish IP.");
    }

    _human_port = human_port;
    _human_ip = human_ip;

    _ip_start = ip_start;
    _ip_current = ip_start;
    _ip_finish = ip_finish; 

    _port_start = port_start;
    _port_current = port_start;
    _port_finish = port_finish;

    _sin.sin_family = AF_INET;
    _sin.sin_addr.s_addr = _human_ip ? htonl(_ip_start) : _ip_start;
    _sin.sin_port = _human_port ? htons(_port_start) : _port_start;
}

DynamicAddress::DynamicAddress(const std::string& ip_from, const std::string& ip_to,
                               uint16_t port_start, uint16_t port_finish,
                               bool human_port) 
{
    if (port_start > port_finish) {
        throw std::range_error("Invalid port range: Start port should be less than Finish port.");
    }    

    inet_pton(AF_INET, ip_from.data(), &_ip_start);
    inet_pton(AF_INET, ip_to.data(), &_ip_finish);

    _ip_start = ntohl(_ip_start);
    _ip_current = _ip_start;
    _ip_finish = ntohl(_ip_finish);

    if (_ip_start > _ip_finish) {
        throw std::range_error("Invalid IP range: Start IP should be less then Finish IP.");
    }
    
    _human_port = human_port;

    _port_start = port_start; 
    _port_current = port_start;
    _port_finish = port_finish;

    _sin.sin_family = AF_INET;
    _sin.sin_addr.s_addr = htonl(_ip_start);
    _sin.sin_port = _human_port ? htons(_port_current) : _port_current;
}

bool 
DynamicAddress::is_completed() {
    return _completed;
}

bool 
DynamicAddress::next() {
    if (_ip_current == _ip_finish && _port_current == _port_finish) {
        _completed = true;
        return false;
    }

    if (_port_current == _port_finish) {
        _port_current = _port_start;
        _ip_current++;
    }
    else {
        _port_current++;
    }

    _sin.sin_addr.s_addr = _human_ip ? htonl(_ip_current) : _ip_current;
    _sin.sin_port = _human_port ? htons(_port_current) : _port_current;
    
    return true;
}

sockaddr_in&
DynamicAddress::get_addr(){
    return _sin;
}

std::string 
DynamicAddress::get_ip_str() {
    inet_ntop(AF_INET, &_sin.sin_addr, _ip_buf, _slen);
    return std::string(_ip_buf);
}

uint16_t
DynamicAddress::get_port() const {
    return ntohs(_sin.sin_port);
}


DAData 
DynamicAddress::get_data() const {
    return {
        .port_start = _port_start,
        .port_finish = _port_finish,
        .ip_start = _ip_start,
        .ip_finish = _ip_finish,
        .human_ip = _human_ip,
        .human_port = _human_port,
    };
}

};
