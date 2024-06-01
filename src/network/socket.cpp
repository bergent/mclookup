#include "network/socket.h"
#include <iostream>

namespace mcnet {

Socket::Socket() {
    fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd < 0) {
        std::cerr << "Error: Unable to create socket\n";
        std::exit(1);
    }
}

};

