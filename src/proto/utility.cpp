#include "proto/utility.h"
#include "proto/messages.h"
#include <iostream>

namespace mcproto {
    
void push_field(uint8_t*& buf, Pushable* field) {
    int shift = field->encode(buf);
    buf = buf + shift;
}

void get_field(uint8_t*& buf, Pushable* field) {
    int shift = field->decode(buf);
    buf += shift;
}

};
