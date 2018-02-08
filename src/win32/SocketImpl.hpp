//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SOCKETIMPL_HPP
#define OKHTTPFORK_SOCKETIMPL_HPP

#include <ohf/Socket.hpp>
#include <ohf/Config.hpp>
#include <string>
#include <ws2tcpip.h>

namespace ohf {
    class SocketImpl {
    public:
        typedef int SocketLength;

        struct Initializer {
            Initializer();

            ~Initializer();
        };

        static sockaddr_in createAddress(Uint32 address, Uint16 port);

        static void close(Socket::Handle sock);

        static std::string getError();

        static void setBlocking(Socket::Handle sock, bool blocking);

        static Socket::Handle invalidSocket();
    };
}

#endif //OKHTTPFORK_SOCKETIMPL_HPP
