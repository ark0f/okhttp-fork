//
// Created by Good_Pudge.
//

#include <iostream>
#include <ohf/Exception.hpp>
#include <ohf/InetAddress.hpp>

int main() {
    try {
        ohf::InetAddress address("www.google.com", ohf::IPv4);
        std::cout << "Official host name:   " << address.hostName() << std::endl;
        std::cout << "IP address as string: " << address.hostAddress() << std::endl;

    } catch (const ohf::Exception &e) {
        std::cerr << e.message() << std::endl;
    }
}