//
// Created by Senya on 02.09.2017.
//

#include <iostream>
#include <ohf/Exception.hpp>
#include <ohf/SSLSocket.hpp>

int main() {
    // Same API as TCPSocket but have function `sni(const std::string &host_name)`

    try {
        ohf::HttpURL url = "https://yandex.ru";

        ohf::SSLSocket sslSocket;
        sslSocket.connect(url); // port specified by protocol `https`
        sslSocket.sni(url.host());


        std::iostream &ios = sslSocket.stream();
        ios << "GET / HTTP/1.1\r\n"
            << "Host: " << url.host() << "\r\n"
            << "Connection: close\r\n"
            << "\r\n";

        std::cout << ios.rdbuf() << std::endl;

        sslSocket.disconnect();
    } catch (ohf::Exception &e) {
        std::cout << e.what() << std::endl << "\tCode: " << e.code() << std::endl;
    }
}