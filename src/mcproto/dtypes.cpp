#include "mcproto/dtypes.h"
#include <arpa/inet.h>
#include <cstring>

namespace mcproto {

// VarInt

int VarInt::encode() {
    uint32_t copy = underlying;
    int pos = 0;

    do 
    {
        uint8_t byte = copy & DATA_MASK; 
        copy >>= SHIFT;

        if (copy) {
            byte |= NEXT_BIT;
        }
        
        encoded[pos++] = byte;
    }
    while (copy);

    size = pos;
    return size;
}

int VarInt::decode(uint8_t* buf, int offset){
    uint32_t value = 0;
    int shift = 0;
    int times_shifted = 0;

    do 
    {
        uint8_t byte = buf[offset++];
        value |= (uint32_t)(byte & DATA_MASK) << shift;
        shift += SHIFT;
    } 
    while ((buf[times_shifted++] & NEXT_BIT) != 0);
    
    underlying = value;
    size = times_shifted;

    return size;
}

int VarInt::push(uint8_t* buf) {
    if (size == 0) {
        return 0;
    }

    std::memcpy(buf, encoded, size);
    pushed = size;
    return pushed;
}

// VarLong

int VarLong::encode() {
    uint64_t copy = underlying;
    int pos = 0;

    do 
    {
        uint8_t byte = copy & DATA_MASK; 
        copy >>= SHIFT;

        if (copy) {
            byte |= NEXT_BIT;
        }
        
        encoded[pos++] = byte;
    }
    while (copy);
    size = pos;

    return size;
}

int VarLong::decode(uint8_t* buf, int offset){
    uint64_t value = 0;
    int shift = 0;
    int times_shifted = 0;
    
    do 
    {
        uint8_t byte = buf[offset++];
        value |= (uint32_t)(byte & DATA_MASK) << shift;
        shift += SHIFT;
    } 
    while ((buf[times_shifted++] & NEXT_BIT) != 0);
    
    underlying = value;
    size = times_shifted;

    return size;
}

int VarLong::push(uint8_t* buf) {
    std::memcpy(buf, encoded, size);
    pushed = size;
    return pushed;
}


// String

int String::encode() {
    int offset = 0;

    underlying_size.encode();
    offset += underlying_size.push(encoded);

    std::memcpy(encoded + offset, underlying.data(), underlying.size());
    size = underlying_size.size + underlying.size();
    return size;
}

int String::decode(uint8_t* buf, int offset) {
    underlying_size.decode(buf, offset);
    underlying.resize(underlying_size.underlying);
    
    std::memcpy(underlying.data(), buf + underlying_size.size, underlying.size());
    size = underlying_size.size + underlying.size();
    return size;
}

int String::push(uint8_t* buf) {
    std::memcpy(buf, encoded, size);
    return size;
}


// UShort
int UShort::encode() {
    uint16_t little_endian = htons(underlying);
    std::memcpy(encoded, &little_endian, size);
    return size;
}

int UShort::decode(uint8_t* buf, int offset)  {
    uint16_t little_endian = 0;
    std::memcpy(&little_endian, buf + offset, size);
    underlying = ntohs(little_endian);
    return size;
}

int UShort::push(uint8_t* buf) {
    std::memcpy(buf, encoded, size);
    return size;
}

} // namespace mcproto
