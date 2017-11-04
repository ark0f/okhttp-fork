//
// Created by good-pudge on 01.11.17.
//

#include <cstring>
#include "SocketImpl.hpp"

namespace ohf {
    sockaddr_in SocketImpl::createAddress(Uint32 address, Uint16 port) {
        sockaddr_in sock_addr;
        std::memset(&sock_addr, 0, sizeof(sockaddr_in));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_port = htons(port);
        sock_addr.sin_addr.s_addr = htonl(address);

        return sock_addr;
    }

    void SocketImpl::close(int sock) {
        ::close(sock);
    }

    std::string SocketImpl::getError() {
        return std::string(strerror(errno));
    }

    int SocketImpl::invalidSocket() {
        return -1;
    }
}