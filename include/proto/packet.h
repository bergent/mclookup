#ifndef __H_MCPROTO_PACKET__
#define __H_MCPROTO_PACKET__

#include "proto/base_message.h"
#include "proto/header.h"

namespace mcproto {

struct Packet {
    ~Packet();
    
    uint8_t buf [2048];
    int size {0};

    Header header;
    Message* body {nullptr};

    int encode(uint8_t* buf);
    int decode(uint8_t* buf);
};

}

#endif
