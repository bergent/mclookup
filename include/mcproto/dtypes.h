#ifndef __H_MCPROTO_DTYPES__
#define __H_MCPROTO_DTYPES__

#include <cstdint>
#include <string>

namespace mcproto {

struct Pushable {
    virtual ~Pushable() = default;
    
    int pushed {0};
    uint8_t* encoded = nullptr;

    virtual int push(uint8_t* buf) = 0;
    virtual int encode() = 0;
    virtual int decode(uint8_t* buf, int offset) = 0;
};


struct VarBase {
    const uint8_t NEXT_BIT = 0x80;
    const uint8_t DATA_MASK = 0x7F;
    const int SHIFT = 7;

    virtual ~VarBase() = default;

    int size {0};
    uint8_t position {0};
    uint8_t* encoded {nullptr};
};


struct VarInt : VarBase, Pushable {
    VarInt() = default;
    ~VarInt() {delete[] encoded;}

    VarInt(int32_t data)
        : underlying {data}
    {}

    uint8_t* encoded = new uint8_t[5];
    int32_t underlying {0};

    virtual int push(uint8_t* buf) override;
    virtual int encode() override;
    virtual int decode(uint8_t* buf, int offset) override;

    VarInt& operator= (VarInt&& other) {
        underlying = other.underlying;
        encoded = other.encoded;
        other.encoded = nullptr;
        return *this;
    }
};

struct VarLong : VarBase, Pushable {
    VarLong() = default;
    ~VarLong() {delete[] encoded;}

    VarLong(int64_t data) 
        : underlying {data}
    {}

    uint8_t* encoded = new uint8_t[10];
    int64_t underlying {0};

    virtual int push(uint8_t* buf) override;
    virtual int encode() override;
    virtual int decode(uint8_t* buf, int offset) override;

    VarLong& operator= (VarLong&& other) {
        underlying = other.underlying;
        encoded = other.encoded;
        other.encoded = nullptr;
        return *this;
    }
};

struct String : Pushable {
    String() = default;
    ~String() {delete[] encoded;}

    String(const std::string& data)
        : underlying {data}, 
          underlying_size {static_cast<int32_t>(data.size())}
    {
        encoded = new uint8_t[underlying.size() + underlying_size.size];
    }

    int size {0};
    std::string underlying {""};
    VarInt underlying_size {0};

    virtual int push(uint8_t* buf) override;
    virtual int encode() override;
    virtual int decode(uint8_t* buf, int offset) override;

    String& operator= (String&& other) {
        underlying = std::move(other.underlying);
        underlying_size = std::move(other.underlying_size);
        encoded = other.encoded;
        other.encoded = nullptr;
        return *this;
    }
};

struct UShort : Pushable {
    UShort() = default;
    ~UShort() {delete[] encoded;}

    UShort(uint16_t data)
        : underlying {data}
    {
        encoded = new uint8_t[2];
    }
    
    int size {2};
    uint16_t underlying;

    virtual int push(uint8_t* buf) override;
    virtual int encode() override;
    virtual int decode(uint8_t* buf, int offset) override;

    UShort& operator= (UShort&& other) {
        underlying = other.underlying;
        encoded = other.encoded;
        other.encoded = nullptr;
        return *this;
    }
};

};


#endif
