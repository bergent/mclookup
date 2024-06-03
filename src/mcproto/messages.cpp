#include "mcproto/messages.h"
#include "mcproto/base_message.h"
#include "mcproto/utility.h"
#include <cstring>

namespace mcproto {

// Handshake

int Handshake::encode(uint8_t* begin) {
    uint8_t* safe_copy = begin;
    
    push_field(safe_copy, &protocol_version);
    push_field(safe_copy, &server_address);
    push_field(safe_copy, &server_port);
    push_field(safe_copy, &next_state);

    return safe_copy - begin;
}

int Handshake::decode(uint8_t* begin) {
    uint8_t* safe_copy = begin;
    
    get_field(safe_copy, &protocol_version);
    get_field(safe_copy, &server_address); 
    get_field(safe_copy, &server_port);
    get_field(safe_copy, &next_state);

    return safe_copy - begin;
}


// Status Request

int StatusRequest::encode([[maybe_unused]] uint8_t* begin) {
    return 0;
}

int StatusRequest::decode([[maybe_unused]] uint8_t* begin) {
    return 0;
}

};
