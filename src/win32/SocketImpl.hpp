//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_WIN_SOCKETIMPL_HPP
#define OKHTTPFORK_WIN_SOCKETIMPL_HPP

#include <ohf/Socket.hpp>
#include <ohf/Config.hpp>

#define _WIN32_WINNT 0x600
#include <winsock2.h>
#include <ws2tcpip.h>

namespace ohf {
    namespace SocketImpl {
        typedef int SocketLength;

        struct Initializer {
            Initializer();

            ~Initializer();
        };

        void close(Socket::Handle sock);

        std::string getError();

        void setBlocking(Socket::Handle sock, bool blocking);

        Socket::Handle invalidSocket();
    };
}

#endif // OKHTTPFORK_WIN_SOCKETIMPL_HPP
