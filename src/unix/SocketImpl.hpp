//
// Created by good-pudge on 01.11.17.
//

#ifndef OKHTTPFORK_UNIX_SOCKETIMPL_HPP
#define OKHTTPFORK_UNIX_SOCKETIMPL_HPP

#include <ohf/Socket.hpp>
#include <ohf/Config.hpp>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>

namespace ohf {
    namespace SocketImpl {
        typedef socklen_t SocketLength;

        struct Initializer {};

        void close(Socket::Handle sock);

        std::string getError();

        void setBlocking(Socket::Handle sock, bool blocking);

        Socket::Handle invalidSocket();
    };
}

#endif //OKHTTPFORK_SOCKETIMPL_HPP
