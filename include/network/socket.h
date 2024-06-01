#ifndef __H_NETWORK_SOCKET__
#define __H_NETWORK_SOCKET__

#include <sys/socket.h>
#include <arpa/inet.h>

namespace mcnet {

struct Socket {
    Socket();
    ~Socket();

    int fd;
};

};


#endif
