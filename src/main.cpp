#include "mcproto/messages.h"
#include "mcproto/dtypes.h"
#include <iostream>

int main() {
    uint8_t buf[128];

    mcproto::Handshake handshake;
    handshake.protocol_version = mcproto::VarInt(-1);
    handshake.server_address = mcproto::String("127.0.0.1");
    handshake.server_port = mcproto::UShort(2123);
    handshake.next_state = mcproto::VarInt(1);

    int encoded = handshake.encode(buf);
    std::cout << "Encoded " << encoded << " bytes\n";

    mcproto::Handshake recieving;
    int decoded = recieving.decode(buf);
    std::cout << "Decoded " << decoded << " bytes\n";
    
    std::cout << "Decoded Proto Version: " << recieving.protocol_version.underlying << '\n';
    std::cout << "Decoded IP: " << recieving.server_address.underlying << '\n';
    std::cout << "Decoded Port: " << recieving.server_port.underlying << '\n';
    std::cout << "Decoded Next State: " << recieving.next_state.underlying << '\n';
    
}
