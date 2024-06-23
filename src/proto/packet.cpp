#include "proto/packet.h"
#include <cstring>

namespace mcproto {

Packet::~Packet() {
    if (body) 
        delete body;
}

int Packet::encode(uint8_t* buf) {
    uint8_t hdr_buf[8];
    int body_size = body->encode(buf);

    header.packet_size = VarInt(body_size + 1);
    header.message_type = VarInt(body->type);
    
    int hdr_size = header.encode(hdr_buf);

    std::memmove(buf + hdr_size, buf, body_size);
    std::memmove(buf, hdr_buf, hdr_size);

    size = hdr_size + body_size;
    return size;
}

int Packet::decode(uint8_t* buf) {
    int hdr_size = header.decode(buf);
    int body_size = body->decode(buf + hdr_size);

    size = hdr_size + body_size;
    return size;
}

}
