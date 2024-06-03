#ifndef __H_MCPROTO_BASE_MESSAGE__
#define __H_MCPROTO_BASE_MESSAGE__

#include <cstdint>

namespace mcproto {

enum msg_type {
    e_header = -1,
    e_handshake = 0x00,
    e_status_request = 0x00,
    e_status_response = 0x00,
    e_undefined = 0xff,
};

struct Message {
    virtual ~Message() = default;
    
    msg_type type;
    uint32_t size {0};
    
    virtual int encode(uint8_t* begin) = 0;
    virtual int decode(uint8_t* begin) = 0;
};


};


#endif
