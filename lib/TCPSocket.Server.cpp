//
// Created by Good_Pudge.
//

#include <ohf/TCPSocket.hpp>
#include <ohf/Exception.hpp>
#include "SocketImpl.hpp"

namespace ohf {
    TCPSocket::Server::Server() : Socket(Socket::Type::TCP) {}

    TCPSocket::Server::Server(const InetAddress &address, Uint16 port) : Server() {
        bind(address, port);
    }

    TCPSocket::Server::Server(const HttpURL &url) : Server() {
        bind(url);
    }

    void TCPSocket::Server::bind(const InetAddress &address, Uint16 port) {
        create();

        sockaddr_in socket_address = SocketImpl::createAddress(address.toUint32(), port);
        if(::bind(mFD, (sockaddr *) &socket_address, sizeof(sockaddr_in)) == -1) {
            throw Exception(Exception::Code::FAILED_TO_BIND_SOCKET,
                            "Failed to bind socket: " + SocketImpl::getError());
        }
    }

    void TCPSocket::Server::bind(const HttpURL &url) {
        bind(InetAddress(url.host()), url.port());
    }

    void TCPSocket::Server::listen(Int32 count) const {
        if(::listen(mFD, count) < 0) {
            throw Exception(Exception::Code::FAILED_TO_LISTEN_SOCKET,
                            "Failed to listen socket: " + SocketImpl::getError());
        }
    }

    void TCPSocket::Server::listen() const {
        listen(SOMAXCONN);
    }

    TCPSocket TCPSocket::Server::accept() const {
        Socket::Handle fd = ::accept(mFD, nullptr, nullptr);
        if(fd < 0) {
            throw Exception(Exception::Code::FAILED_TO_ACCEPT_SOCKET,
                            "Failed to accept socket: " + SocketImpl::getError());
        }

        TCPSocket client;
        client.create(fd);

        return client;
    }

    const TCPSocket::Server::Iterator TCPSocket::Server::begin() const {
        return {this};
    }

    TCPSocket::Server::Iterator TCPSocket::Server::begin() {
        return {this};
    }

    const TCPSocket::Server::Iterator TCPSocket::Server::end() const {
        return {this};
    }

    TCPSocket::Server::Iterator TCPSocket::Server::end() {
        return {this};
    }
}