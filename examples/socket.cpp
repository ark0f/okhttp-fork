//
// Created by Senya on 02.09.2017.
//

#include <iostream>
#include <ohf/Exception.hpp>
#include <ohf/tcp/Socket.hpp>

int main() {
    try {
        ohf::tcp::Socket socket;
        socket.connect("www.google.com", 80);

        ohf::tcp::Socket::Stream stream(socket);
        stream << "GET / HTTP/1.1\r\n"
            << "Host: www.google.com\r\n"
            << "Connection: close\r\n"
            << "\r\n";
        stream.flush();

        std::cout << stream.rdbuf() << std::endl; // better if you don't do it
        socket.disconnect(); // or close() or destructor do it
    } catch (ohf::Exception &e) {
        std::cout << e.what() << std::endl;
    }
}