#include "network/socket.h"
#include <iostream>
#include <sys/socket.h>

namespace mcnet {

Socket::Socket() {
    fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    if (fd < 0) {
        perror("Unable to create socket: ");
        std::exit(1);
    }
}

Socket::~Socket() {
    int rc = shutdown(fd, SHUT_RDWR);
}

};

