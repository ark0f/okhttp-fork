//
// Created by Good_Pudge.
//

#include <ohf/TCPSocket.hpp>
#include "SocketImpl.hpp"

namespace ohf {
    TCPSocket::Server::Iterator::Iterator(const Server *server) : server(server) {}

    TCPSocket TCPSocket::Server::Iterator::operator*() const {
        return server->accept();
    }

    TCPSocket TCPSocket::Server::Iterator::operator*() {
        return server->accept();
    }

    TCPSocket TCPSocket::Server::Iterator::operator->() const {
        return server->accept();
    }

    TCPSocket TCPSocket::Server::Iterator::operator->() {
        return server->accept();
    }

    const TCPSocket::Server::Iterator& TCPSocket::Server::Iterator::operator++(Int32) const {
        return *this;
    }

    const TCPSocket::Server::Iterator& TCPSocket::Server::Iterator::operator++() const {
        return *this;
    }

    bool TCPSocket::Server::Iterator::operator!=(const Iterator &right) const {
        return server->fd() != SocketImpl::invalidSocket()
               || right.server->fd() != SocketImpl::invalidSocket();
    }
}