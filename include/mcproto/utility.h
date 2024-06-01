#ifndef __H_MCPROTO_UTILITY__
#define __H_MCPROTO_UTILITY__

#include <cstdint>

namespace mcproto {
    struct Pushable;  

    void push_field(uint8_t*& buf, Pushable* field);
    void get_field(uint8_t*& buf, Pushable* field);

};

#endif
