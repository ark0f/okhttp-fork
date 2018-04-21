//
// Created by Good_Pudge.
//

#include <ohf/Exception.hpp>
#include <ohf/udp/Socket.hpp>
#include <iostream>

int main() {
    try {
        ohf::udp::Socket socket;

        socket.send("www.udp-server.com", 1337, "Some request");

        ohf::InetAddress address;
        unsigned short port;
        std::vector<char> response(1024);
        int received = socket.receive(address, port, response.data(), (int) response.size());

        std::cout << std::string(response.begin(), response.end()) << std::endl;
    } catch(const ohf::Exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}