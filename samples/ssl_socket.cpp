//
// Created by Senya on 02.09.2017.
//

#include <iostream>
#include <ohf/Exception.hpp>
#include <ohf/tcp/SSLSocket.hpp>
#include <ohf/ssl/Initializer.hpp>

int main() {
    /**
     * Same API as tcp::Socket, but
     * 1. have functions
     *      void sni(const InetAddress &address)
     *      void sni(bool b)
     * 2. need once global initialize (for OpenSSL)
     * 3. need ssl::Context
     */

    ohf::ssl::Initializer initializer; // no any exception

    try {
        ohf::HttpURL url = "https://yandex.ru";

        ohf::ssl::Context context(ohf::TLSVersion::SSLv23);
        ohf::tcp::SSLSocket sslSocket(context);
        sslSocket.connect(url); // port specified by protocol `https`
        sslSocket.sni(ohf::InetAddress(url.host()));

        std::iostream &ios = sslSocket.stream();
        ios << "GET / HTTP/1.1\r\n"
            << "Host: " << url.host() << "\r\n"
            << "Connection: close\r\n"
            << "\r\n";

        std::cout << ios.rdbuf() << std::endl;

        sslSocket.disconnect();
    } catch (ohf::Exception &e) {
        std::cout << e.what() << std::endl
                  << '\t' << "Code: " << (int) e.code() << std::endl;
    }
}