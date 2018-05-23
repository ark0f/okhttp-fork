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

        Server::Server(Family family, const HttpURL &url) : Server() {
            bind(InetAddress(url.host(), family), url.port());
        }

        Server::Server(ohf::tcp::Server &&server) noexcept {
            mFD = server.mFD;
            server.mFD = SocketImpl::invalidSocket();

            mBlocking = server.mBlocking;
            server.mBlocking = true;
        }

        void Server::bind(const InetAddress &address, Uint16 port) {
            create(address.family());
            mFamily = address.family();

            Int32 option = 1;
            if(setsockopt(mFD, SOL_SOCKET, SO_REUSEADDR, (const char *) &option, sizeof(option)) < 0) {
                throw Exception(Exception::Code::FAILED_TO_SET_SOCKET_OPTION,
                                "Failed to set socket option: " + std::to_string(SO_REUSEADDR));
            }

            SocketImpl::SocketLength length;
            sockaddr_storage socket_address = SocketImpl::createAddress(address, port, length);
            if (::bind(mFD, (sockaddr *) &socket_address, length) == -1) {
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
            sockaddr_storage addr;
            SocketImpl::SocketLength length = SocketImpl::addressLength(mFamily);

            auto fd = ::accept(mFD, (sockaddr *) &addr, &length);
            if (fd == SocketImpl::invalidSocket()) {
                throw Exception(Exception::Code::FAILED_TO_ACCEPT_SOCKET,
                        "Failed to accept socket: " + SocketImpl::getError());
            }

            auto client = new tcp::Socket;
            client->create(fd);

            return {client, SocketImpl::createInetAddress(&addr), SocketImpl::port(&addr)};
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

        Server& Server::operator =(ohf::tcp::Server&& right) noexcept {
            mFD = right.mFD;
            right.mFD = SocketImpl::invalidSocket();

            mBlocking = right.mBlocking;
            right.mBlocking = true;

            return *this;
        }
    }
}

namespace std {
    using namespace ohf;

    void swap(tcp::Server& a, tcp::Server& b) {
        swap(a.mFD, b.mFD);
        swap(a.mBlocking, b.mBlocking);
    }
}