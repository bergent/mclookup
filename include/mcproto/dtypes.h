#ifndef __H_MCPROTO_DTYPES__
#define __H_MCPROTO_DTYPES__

#include <cstdint>
#include <string>

namespace mcproto {

struct Pushable {
    virtual ~Pushable() = default;
    
    int size {0};

    virtual int encode(uint8_t* buf) = 0;
    virtual int decode(uint8_t* buf) = 0;
};


inline constexpr uint8_t VAR_DATA_MASK {0x7f};
inline constexpr uint8_t VAR_NEXT_BIT {0x80};
inline constexpr uint8_t VAR_BYTE_SHIFT {7};

struct VarInt : Pushable {
    VarInt() = default;
    ~VarInt() = default;

    VarInt(const VarInt& other)
        : value {other.value}
    {}

    VarInt(int32_t data)
        : value {data}
    {}
    
    int32_t value {0};

    virtual int encode(uint8_t* buf) override;
    virtual int decode(uint8_t* buf) override;

    VarInt& operator= (const VarInt& other) {
        value = other.value;
        return *this;
    }
};

struct VarLong : Pushable {
    VarLong() = default;
    ~VarLong() = default;

    VarLong(const VarLong& other)
        : value {other.value}
    {}

    VarLong(int64_t data) 
        : value {data}
    {}
    
    int64_t value {0};

    virtual int encode(uint8_t* buf) override;
    virtual int decode(uint8_t* buf) override;
    
    VarLong& operator= (const VarLong& other) {
        value = other.value;
        return *this;
    }
};

struct String : Pushable {
    String() = default;
    ~String() = default;

    String(const String& other) 
        : str {other.str},
          str_size {other.str_size} 
    {}

    String(const std::string& data)
        : str {data}, 
          str_size {static_cast<int32_t>(data.size())}
    {}

    std::string str {""};
    VarInt str_size {0};

    virtual int encode(uint8_t* buf) override;
    virtual int decode(uint8_t* buf) override;
    
    String& operator= (const String& other) {
        str = other.str;
        str_size = other.str_size;
        return *this;
    }
};

struct UShort : Pushable {
    UShort() = default;
    ~UShort() = default;
    
    UShort(const UShort& other)
        : value {other.value}
    {}

    UShort(uint16_t data)
        : value {data}
    {}
    
    int size {2};
    uint16_t value;

    virtual int encode(uint8_t* buf) override;
    virtual int decode(uint8_t* buf) override;
    
    UShort& operator= (const UShort& other) {
        value = other.value;
        return *this;
    }
};

};


#endif
