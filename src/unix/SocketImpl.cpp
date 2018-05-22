//
// Created by good-pudge on 01.11.17.
//

#include <cstring>
#include <sys/ioctl.h>
#include "SocketImpl.hpp"

namespace ohf {
    void SocketImpl::close(Socket::Handle sock) {
        ::close(sock);
    }

    std::string SocketImpl::getError() {
        return strerror(errno);
    }

    void SocketImpl::setBlocking(Socket::Handle sock, bool blocking) {
        unsigned long mode = blocking ? 0 : 1;
        ioctl(sock, FIONBIO, &mode);
    }

    Socket::Handle SocketImpl::invalidSocket() {
        return -1;
    }
}