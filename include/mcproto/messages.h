#ifndef __H_MCPROTO_MESSAGES__
#define __H_MCPROTO_MESSAGES__

#include "mcproto/base_message.h"
#include "mcproto/dtypes.h"

namespace mcproto {

struct Handshake : Message {
    Handshake() = default;
    Handshake(const Handshake& other) {*this = other;}

    ~Handshake() = default;

    mcproto::VarInt protocol_version;
    mcproto::VarInt next_state;
    mcproto::String server_address;
    mcproto::UShort server_port;

    virtual int encode(uint8_t* begin) override;
    virtual int decode(uint8_t* begin) override;

    Handshake& operator= (const Handshake& other) {
        size = other.size;
        protocol_version = other.protocol_version;
        next_state = other.next_state;
        server_address = other.server_address;
        server_port = other.server_port;
        return *this;
    }
};

struct StatusRequest : Message {
    StatusRequest() = default;
    StatusRequest(const StatusRequest& other) {*this = other;}
    ~StatusRequest() = default;

    uint32_t size {0};

    virtual int encode(uint8_t* begin) override;
    virtual int decode(uint8_t* begin) override;

    StatusRequest& operator= (const StatusRequest& other) {
        size = other.size;
        return *this;
    }
};

struct StatusResponse : Message {
    StatusResponse() = default;
    StatusResponse(const StatusRequest& other) {*this = other;}
    ~StatusResponse() = default;

    mcproto::String json_response;

    virtual int encode(uint8_t* begin) override;
    virtual int decode(uint8_t* begin) override;

    StatusResponse& operator= (const StatusResponse& other) {
        size = other.size;
        json_response = other.json_response;
        return *this;
    }
};

};
#endif
