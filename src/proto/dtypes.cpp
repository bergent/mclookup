#include "proto/dtypes.h"
#include <arpa/inet.h>
#include <cstring>

namespace mcproto {

// --- VarInt --- 

int VarInt::encode(uint8_t* buf) {
    uint32_t copy_value = value;
    uint8_t* copy_ptr = buf;

    do 
    {
        uint8_t byte = copy_value & VAR_DATA_MASK; 
        copy_value >>= VAR_BYTE_SHIFT;

        if (copy_value) {
            byte |= VAR_NEXT_BIT;
        }
        
        *copy_ptr = byte;
        copy_ptr++;
    }
    while (copy_value);
    
    size = copy_ptr - buf;
    return size;
}

int VarInt::decode(uint8_t* buf){
    int32_t decoded = 0;
    uint8_t* copy_ptr = buf;

    int shift = 0;

    do 
    {
        uint8_t byte = *copy_ptr;

        decoded |= (uint32_t)(byte & VAR_DATA_MASK) << shift;
        shift += VAR_BYTE_SHIFT;
    } 
    while ((*(copy_ptr++) & VAR_NEXT_BIT) != 0);
    
    value = decoded;
    size = copy_ptr - buf;
    return size;
}


// --- VarLong ---

int VarLong::encode(uint8_t* buf) {
    uint64_t copy_value = value;
    uint8_t* copy_ptr = buf;

    do 
    {
        uint8_t byte = copy_value & VAR_DATA_MASK; 
        copy_value >>= VAR_BYTE_SHIFT;

        if (copy_value) {
            byte |= VAR_NEXT_BIT;
        }
        
        *copy_ptr = byte;
        copy_ptr++;
    }
    while (copy_value);
    
    size = copy_ptr - buf;
    return size;
}

int VarLong::decode(uint8_t* buf){
    int64_t decoded = 0;
    uint8_t* copy_ptr = buf;

    int shift = 0;

    do 
    {
        uint8_t byte = *copy_ptr;

        decoded |= (uint64_t)(byte & VAR_DATA_MASK) << shift;
        shift += VAR_BYTE_SHIFT;
    } 
    while ((*(copy_ptr++) & VAR_NEXT_BIT) != 0);
    
    value = decoded;
    size = copy_ptr - buf;
    return size;
}



// --- String --- 

int String::encode(uint8_t* buf) {
    int offset = str_size.encode(buf);

    std::memcpy(buf + offset, str.data(), str.size());

    size = str_size.size + str.size();
    return size;
}

int String::decode(uint8_t* buf) {
    int offset = str_size.decode(buf);
    str.resize(str_size.value);

    std::memcpy(str.data(), buf + offset, str_size.value);
        
    size = str_size.size + str.size();
    return size;
}


// --- UShort --- 

int UShort::encode(uint8_t* buf) {
    uint16_t little_endian = htons(value);
    std::memcpy(buf, &little_endian, size);

    return size;
}

int UShort::decode(uint8_t* buf)  {
    uint16_t little_endian = 0;
    std::memcpy(&little_endian, buf, size);
    value = ntohs(little_endian);

    return size;
}

} // namespace mcproto
