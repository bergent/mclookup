#include "mcproto/utility.h"
#include "mcproto/messages.h"
#include <iostream>

namespace mcproto {
    
void push_field(uint8_t*& buf, Pushable* field) {
    field->encode();
    int shift = field->push(buf);
    buf = buf + shift;
}

void get_field(uint8_t*& buf, Pushable* field) {
    int shift = field->decode(buf, 0);
    buf += shift;
}

};
