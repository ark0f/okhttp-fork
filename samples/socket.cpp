//
// Created by Senya on 02.09.2017.
//

#include <iostream>
#include <ohf/Exception.hpp>
#include <ohf/Socket.hpp>

int main() {
    try {
        ohf::Socket socket;
        std::iostream &ios = socket.connect("www.yandex.ru", 80);

        ios << "GET / HTTP/1.1\r\n";
        ios << "Host: www.yandex.ru\r\n";
        ios << "Connection: close\r\n\r\n";

        std::cout << ios.rdbuf() << std::endl;
        socket.shutdown();
    } catch (ohf::Exception &e) {
        std::cout << e.what() << std::endl << "\tCode: " << e.code() << std::endl;
    }
}