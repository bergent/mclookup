#include "mcproto/base_message.h"
#include "mcproto/dtypes.h"
#include "mcproto/header.h"
#include "mcproto/messages.h"
#include "mcproto/packet.h"
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
    uint8_t buf [100];
    uint8_t status_buf [100];
    
    mcproto::Packet packet; 
    packet.header.message_type = mcproto::VarInt(mcproto::e_handshake);
    
    packet.body = new mcproto::Handshake;
    auto hs = static_cast<mcproto::Handshake*>(packet.body);
    hs->protocol_version = mcproto::VarInt(765);
    hs->server_address = mcproto::String("89.33.12.0");
    hs->server_port = mcproto::UShort(25565);
    hs->next_state = mcproto::VarInt(1);

    int encoded = packet.encode(buf);
    std::cout << "Encoded " << encoded << " bytes\n";


    mcproto::Packet recv;
    int decoded_hdr = recv.header.decode(buf);

    if (recv.header.message_type.value == mcproto::e_handshake)
        recv.body = new mcproto::Handshake;

    auto ptr = static_cast<mcproto::Handshake*>(recv.body);

    int decoded_body = recv.body->decode(buf + decoded_hdr);
    std::cout << "Decoded header: " << decoded_hdr << " bytes\n";
    std::cout << "Decoded body: " << decoded_body << " bytes\n";
    std::cout << "Decoded total: " << decoded_hdr + decoded_body << " bytes\n";

    std::cout << "Protocol Version: " << ptr->protocol_version.value << '\n';
    std::cout << "Server Address: " << ptr->server_address.str << '\n';
    std::cout << "Server Port: " << ptr->server_port.value << '\n';
    std::cout << "Next State: " << ptr->next_state.value << '\n';

    mcproto::Packet status;
    status.header.message_type = mcproto::VarInt(mcproto::e_status_request);
    status.body = new mcproto::StatusRequest;
    
    int status_encoded = status.encode(status_buf);

    std::cout << "Status Encoded: " << status_encoded << " bytes\n";


    int fd = socket(AF_INET, SOCK_STREAM, 0);
    
    std::string ip {"89.33.12.0"};
    uint16_t port = 25565;
    addr mc_server;
    

    inet_pton(AF_INET, ip.data(), &mc_server.sin.sin_addr);
    mc_server.sin.sin_family = AF_INET;
    mc_server.sin.sin_port = htons(port);
    
    int connect_rc = connect(fd, &mc_server.sa, sizeof(mc_server));
    if (connect_rc != 0) {
        perror("Connect");
    }

    int send_hs_rc = send(fd, buf, encoded, 0);
    if (send_hs_rc < 0) {
        perror("Send Handshake");
    }

    int send_status_rc = send(fd, status_buf, status_encoded, 0);
    if (send_status_rc < 0) {
        perror("Send Status");
    }

    uint8_t recv_buf [1024];


}
