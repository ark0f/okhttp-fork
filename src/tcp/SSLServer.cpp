//
// Created by Good_Pudge.
//

#include <ohf/tcp/SSLServer.hpp>
#include <ohf/tcp/SSLSocket.hpp>
#include <ohf/Exception.hpp>
#include "../SocketImpl.hpp"
#include "../ssl/Util.hpp"

namespace ohf {
    namespace tcp {
        SSLServer::SSLServer(const ssl::Context &context) :
                ohf::Socket(Type::TCP),
                ssl::Socket(Type::TCP, context)
        {}

        SSLServer::SSLServer(ohf::tcp::SSLServer&& server) noexcept : ssl::Socket(Type::TCP, server.context) {
            mFD = server.mFD;
            server.mFD = SocketImpl::invalidSocket();

            mBlocking = server.mBlocking;
            server.mBlocking = true;

            mSSL = std::move(server.mSSL);
        }

        SSLServer::Connection SSLServer::accept() const {
            sockaddr_in addr;
            SocketImpl::SocketLength length = sizeof(addr);

            auto fd = ::accept(ssl::Socket::mFD, (sockaddr *) &addr, &length);
            if (fd == SocketImpl::invalidSocket()) {
                throw Exception(Exception::Code::FAILED_TO_ACCEPT_SOCKET,
                        "Failed to accept socket: " + SocketImpl::getError());
            }

            auto *client = new tcp::SSLSocket(context);
            client->create(fd);
            client->accept();

            return {client, InetAddress(*(Uint32 *) &addr.sin_addr), addr.sin_port};
        }

        void SSLServer::bind(const InetAddress &address, Uint16 port) {
            ssl::Socket::create();

            Server::bind(address, port);
        }

        SSLServer& SSLServer::operator =(ohf::tcp::SSLServer&& right) noexcept {
            mFD = right.mFD;
            right.mFD = SocketImpl::invalidSocket();

            mBlocking = right.mBlocking;
            right.mBlocking = true;

            mSSL = std::move(right.mSSL);

            return *this;
        }
    }
}

namespace std {
    using namespace ohf;

    void swap(tcp::SSLServer& a, tcp::SSLServer& b) {
        swap(a, b);
        swap(a.mSSL, b.mSSL);
    }
}