//
// Created by Good_Pudge.
//

#include <cstring>
#include <winsock.h>
#include "SocketImpl.hpp"
#include "WinUtils.hpp"

namespace ohf {
    sockaddr_in SocketImpl::createAddress(Uint32 address, Uint16 port) {
        sockaddr_in sock_addr;
        std::memset(&sock_addr, 0, sizeof(sockaddr_in));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_port = htons(port);
        sock_addr.sin_addr.S_un.S_addr = htonl(address);

        return sock_addr;
    }

    void SocketImpl::close(int sock) {
        closesocket(sock);
    }

    std::string SocketImpl::getError() {
        return getWSAError();
    }

    void SocketImpl::setBlocking(int sock, bool blocking) {
        unsigned long mode = blocking ? 0 : 1;
        ioctlsocket(sock, FIONBIO, &mode);
    }

    Socket::Handle SocketImpl::invalidSocket() {
        return INVALID_SOCKET;
    }
}