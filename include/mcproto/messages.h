#ifndef __H_MCPROTO_MESSAGES__
#define __H_MCPROTO_MESSAGES__

#include "mcproto/base_message.h"
#include "mcproto/dtypes.h"

namespace mcproto {

struct Handshake : Message {
    Handshake() = default;
    ~Handshake() = default;

    msg_type type {e_handshake};
    
    mcproto::VarInt protocol_version;
    mcproto::VarInt next_state;
    mcproto::String server_address;
    mcproto::UShort server_port;

    virtual int encode(uint8_t* begin) override;
    virtual int decode(uint8_t* begin) override;
};

struct StatusRequest : Message {
    StatusRequest() = default;
    ~StatusRequest() = default;

    msg_type type {e_status_request};

    virtual int encode(uint8_t* begin) override;
    virtual int decode(uint8_t* begin) override;
};

struct StatusResponse : Message {
    StatusResponse() = default;
    ~StatusResponse() = default;

    msg_type type {e_status_response};

    mcproto::String json_response;

    virtual int encode(uint8_t* begin) override;
    virtual int decode(uint8_t* begin) override;
};

};
#endif
