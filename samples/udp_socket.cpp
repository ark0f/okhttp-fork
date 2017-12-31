//
// Created by Good_Pudge.
//

#include <ohf/Exception.hpp>
#include <ohf/udp/Socket.hpp>
#include <iostream>

int main() {
    try {
        ohf::UDPSocket socket;

        socket.send("www.udp-server.com", 1337, "Some request");

        ohf::InetAddress address;
        ohf::Uint16 port; // unsigned short
        std::vector<char> response(1024);
        std::size_t received = socket.receive(address, port, response.data(), response.size());

        std::cout << std::string(response.begin(), response.end()) << std::endl;
    } catch(const ohf::Exception &e) {

    }
}