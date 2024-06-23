#include "mcproto/base_message.h"
#include "mcproto/dtypes.h"
#include "mcproto/header.h"
#include "mcproto/messages.h"
#include "mcproto/packet.h"
#include "network/ip.h"
#include "network/socket.h"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>

union addr {
    sockaddr sa;
    sockaddr_in sin;
};

void test_single() {
    uint8_t buf [64];

    mcproto::Handshake hs;
    hs.protocol_version = mcproto::VarInt(-1);
    hs.server_address = mcproto::String("0.0.0.0");
    hs.server_port = mcproto::UShort(2123);
    hs.next_state = mcproto::VarInt(1);

    int encoded = hs.encode(buf);

    std::cout << "Encoded " << encoded << " bytes\n";

    mcproto::Handshake recv;
    int decoded = recv.decode(buf);
    
    std::cout << "Decoded: " << decoded << " bytes\n";
    std::cout << "Protocol Version: " << recv.protocol_version.value << '\n';
    std::cout << "Server Address: " << recv.server_address.str << "\n";
    std::cout << "Server Port: " << recv.server_port.value << '\n';
    std::cout << "Next State: " << recv.next_state.value << '\n';
    

    std::cout << "Handshake: " << mcproto::e_handshake << "\n";
    std::cout << "StatusRequest: " << mcproto::e_status_request << "\n";
    std::cout << "StatusResponse: " << mcproto::e_status_response << "\n";

    mcproto::Header hdr;
    hdr.message_type = mcproto::VarInt{mcproto::e_handshake};
    hdr.packet_size = mcproto::VarInt{16};

    encoded = hdr.encode(buf);
    std::cout << "Encoded " << encoded << " bytes\n";

    mcproto::Header recv_hdr;
    decoded = recv_hdr.decode(buf);
    
    std::cout << "Decoded " << decoded << " bytes\n";
    std::cout << "Packet Size: " << recv_hdr.packet_size.value << '\n';
    std::cout << "Message Type: " << recv_hdr.message_type.value << '\n';
}

int main() {
    mcnet::DynamicAddress daddr {"8.8.8.8", "8.8.8.9", 1000, 1010};
    
    while (true) {
        std::cout << daddr.get_ip_str() << ":" << daddr.get_port() << '\n';

        if (!daddr.next()) {
            break;
        }
    }

    if (daddr.is_completed()) {
        std::cout << "Completed!\n";
    }
}
