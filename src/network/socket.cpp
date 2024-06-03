#include "network/socket.h"
#include <iostream>
#include <sys/socket.h>

namespace mcnet {

Socket::Socket() {
    fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd < 0) {
        std::cerr << "Error: Unable to create socket\n";
        std::exit(1);
    }
}

Socket::~Socket() {
    int rc = shutdown(fd, SHUT_RDWR);
    if (rc < 0) {
        std::cerr << "Error: Socket did not close";
        std::exit(1);
    }
}

};

