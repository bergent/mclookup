#ifndef __H_MCPROTO_HEADER__
#define __H_MCPROTO_HEADER__

#include "mcproto/base_message.h"
#include "mcproto/dtypes.h"

namespace mcproto {

struct Header : Message {
    Header() = default;
    Header(const Header& other) {*this = other;}
    ~Header() = default;

    msg_type type {e_header};
    
    mcproto::VarInt packet_size;
    mcproto::VarInt message_type;

    virtual int encode(uint8_t* begin);
    virtual int decode(uint8_t* begin);
    
    Header& operator= (const Header& other) {
        size = other.size;
        packet_size = other.packet_size;
        message_type = other.message_type;
        return *this;
    }
};
    
};

#endif
