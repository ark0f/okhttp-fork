//
// Created by Senya on 02.09.2017.
//

#include <iostream>
#include "../include/Exception.hpp"
#include "../include/SSLSocket.hpp"

int main() {
    try {
        ohf::SSLSocket sslSocket;
        std::iostream &ios = sslSocket.connect("www.yandex.ru", 443);

        ios << "GET / HTTP/1.1\r\n";
        ios << "Host: www.yandex.ru\r\n";
        ios << "Connection: close\r\n\r\n";

        std::cout << ios.rdbuf() << std::endl;
    } catch (ohf::Exception &e) {
        std::cout << e.what() << std::endl << "\tCode: " << e.code() << std::endl;
    }
}