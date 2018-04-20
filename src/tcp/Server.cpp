//
// Created by Good_Pudge.
//

#include <ohf/Socket.hpp>
#include <ohf/tcp/Server.hpp>
#include <ohf/Exception.hpp>
#include "../SocketImpl.hpp"

namespace ohf {
    namespace tcp {
        Server::Server() : ohf::Socket(Type::TCP) {}

        Server::Server(const InetAddress &address, Uint16 port) : Server() {
            bind(address, port);
        }

        Server::Server(const HttpURL &url) : Server() {
            bind(url);
        }

        void Server::bind(const InetAddress &address, Uint16 port) {
            create();

            sockaddr_in socket_address = SocketImpl::createAddress(address.toUint32(), port);
            if (::bind(mFD, (sockaddr * ) &socket_address, sizeof(sockaddr_in)) == -1) {
                throw Exception(Exception::Code::FAILED_TO_BIND_SOCKET,
                        "Failed to bind socket: " + SocketImpl::getError());
            }
        }

        void Server::bind(const HttpURL &url) {
            bind(InetAddress(url.host()), url.port());
        }

        void Server::listen(Int32 count) const {
            if (::listen(mFD, count) < 0) {
                throw Exception(Exception::Code::FAILED_TO_LISTEN_SOCKET,
                        "Failed to listen socket: " + SocketImpl::getError());
            }
        }

        void Server::listen() const {
            listen(SOMAXCONN);
        }

        Server::Connection Server::accept() const {
            sockaddr_in addr;
            SocketImpl::SocketLength length = sizeof(addr);

            auto fd = ::accept(mFD, (sockaddr *) &addr, &length);
            if (fd == SocketImpl::invalidSocket()) {
                throw Exception(Exception::Code::FAILED_TO_ACCEPT_SOCKET,
                        "Failed to accept socket: " + SocketImpl::getError());
            }

            auto client = new tcp::Socket;
            client->create(fd);

            return {client, InetAddress(*(Uint32 *) &addr.sin_addr), addr.sin_port};
        }

        const Server::Iterator Server::begin() const {
            return {this};
        }

        Server::Iterator Server::begin() {
            return {this};
        }

        const Server::Iterator Server::end() const {
            return {this};
        }

        Server::Iterator Server::end() {
            return {this};
        }
    }
}