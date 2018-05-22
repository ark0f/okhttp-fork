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
        SSLServer::SSLServer(Family family, const ssl::Context &context) :
                Server(family),
                ssl::Socket(Type::TCP, family, context)
        {}

        SSLServer::SSLServer(SSLServer&& server) noexcept :
                Server(server.mFamily),
                ssl::Socket(Type::TCP, server.mFamily, server.context)
        {
            mFD = server.mFD;
            server.mFD = SocketImpl::invalidSocket();

            mBlocking = server.mBlocking;
            server.mBlocking = true;

            mFamily = server.mFamily;
            server.mFamily = Family::UNKNOWN;

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

            auto *client = new tcp::SSLSocket(mFamily, context);
            client->create(fd);
            client->accept();

            return {client, SocketImpl::createInetAddress(&addr), SocketImpl::port(&addr)};
        }

        SSLServer& SSLServer::operator =(SSLServer&& right) noexcept {
            mFD = right.mFD;
            right.mFD = SocketImpl::invalidSocket();

            mBlocking = right.mBlocking;
            right.mBlocking = true;

            mFamily = right.mFamily;
            right.mFamily = Family::UNKNOWN;

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