//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SOCKETIMPL_HPP
#define OKHTTPFORK_SOCKETIMPL_HPP

#include <string>
#include <winsock.h>
#include "../../include/Config.hpp"

namespace ohf {
    class SocketImpl {
    public:
        static sockaddr_in createAddress(Uint32 address, Uint16 port);

        static void close(int sock);

        static std::string getError();

        static void setBlocking(int sock, bool blocking);

        static int invalidSocket();
    };
}

#endif //OKHTTPFORK_SOCKETIMPL_HPP
