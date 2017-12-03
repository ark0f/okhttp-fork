//
// Created by Senya on 02.09.2017.
//

#include <iostream>
#include <ohf/Exception.hpp>
#include <ohf/TCPSocket.hpp>

int main() {
    try {
        ohf::TCPSocket socket("www.yandex.ru", 80);

        std::iostream &ios = socket.stream();
        ios << "GET / HTTP/1.1\r\n"
            << "Host: www.yandex.ru\r\n"
            << "Connection: close\r\n"
            << "\r\n";

        std::cout << ios.rdbuf() << std::endl; // better if you don't do it
        socket.disconnect(); // or close() or destructor do it
    } catch (ohf::Exception &e) {
        std::cout << e.what() << std::endl << "\tCode: " << e.code() << std::endl;
    }
}