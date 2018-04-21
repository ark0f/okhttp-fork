//
// Created by Good_Pudge.
//

#include <iostream>
#include <ohf/Exception.hpp>
#include <ohf/InetAddress.hpp>

int main() {
    try {
        ohf::InetAddress address = "www.google.com";
        std::cout << "Official host name:   " << address.hostName() << std::endl;
        std::cout << "IP address as string: " << address.hostAddress() << std::endl;

        std::vector<unsigned char> ip = address.address();

        std::vector<ohf::InetAddress> addresses = ohf::InetAddress::getAllByName("www.yandex.ru");
    } catch (const ohf::Exception &e) {
        std::cerr << e.message() << std::endl;
    }
}