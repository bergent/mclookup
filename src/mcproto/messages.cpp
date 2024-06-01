#include "mcproto/messages.h"
#include "mcproto/utility.h"
#include <cstring>

namespace mcproto {

// Handshake

int Handshake::encode(uint8_t* begin) {
    uint8_t* safe_copy = begin;
    
    // Message type
    std::memcpy(safe_copy, &type, 1);
    safe_copy += 1;
    
    push_field(safe_copy, &protocol_version);
    push_field(safe_copy, &server_address);
    push_field(safe_copy, &server_port);
    push_field(safe_copy, &next_state);

    return safe_copy - begin;
}

int Handshake::decode(uint8_t* begin) {
    uint8_t* safe_copy = begin;

    // Message type 
    std::memcpy(&type, safe_copy, 1);
    safe_copy += 1;
    
    get_field(safe_copy, &protocol_version);
    get_field(safe_copy, &server_address); 
    get_field(safe_copy, &server_port);
    get_field(safe_copy, &next_state);

    return safe_copy - begin;
}

};
