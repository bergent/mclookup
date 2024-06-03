#include "mcproto/header.h"
#include "mcproto/utility.h"

namespace mcproto {

int Header::encode(uint8_t* begin) {
    uint8_t* safe_copy = begin; 

    push_field(safe_copy, &packet_size);
    push_field(safe_copy, &message_type);
    
    return safe_copy - begin;
}

int Header::decode(uint8_t* begin) {
    uint8_t* safe_copy = begin;

    get_field(safe_copy, &packet_size);
    get_field(safe_copy, &message_type);

    return safe_copy - begin;
}


};
