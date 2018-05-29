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
                Server(),
                ssl::Socket(Type::TCP, context)
        {}

        SSLServer::SSLServer(SSLServer&& server) noexcept :
                Server(),
                ssl::Socket(Type::TCP, server.context)
        {
            mFD = server.mFD;
            server.mFD = SocketImpl::invalidSocket();

            mBlocking = server.mBlocking;
            server.mBlocking = true;

            mSSL = std::move(server.mSSL);
        }

        SSLServer::Connection SSLServer::accept() const {
            sockaddr_storage addr;
            SocketImpl::SocketLength length = SocketImpl::addressLength(mFamily);

            auto fd = ::accept(ssl::Socket::mFD, (sockaddr *) &addr, &length);
            if (fd == SocketImpl::invalidSocket()) {
                throw Exception(Exception::Code::FAILED_TO_ACCEPT_SOCKET,
                        "Failed to accept socket: " + SocketImpl::getError());
            }

            auto *client = new tcp::SSLSocket(context);
            client->create(fd);
            client->ssl().accept();

            return {client, SocketImpl::createInetAddress(&addr), SocketImpl::port(&addr)};
        }

        SSLServer& SSLServer::operator =(SSLServer&& right) noexcept {
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