//
// Created by Good_Pudge.
//

#include <ohf/tcp/SSLServer.hpp>
#include <ohf/Exception.hpp>
#include <ohf/tcp/SSLSocket.hpp>
#include <openssl/ssl.h>
#include "../SocketImpl.hpp"
#include "../ssl/Util.hpp"

namespace ohf {
    namespace tcp {
        SSLServer::SSLServer(const ssl::Context &context) : ssl::Socket(Type::TCP, context) {}

        void SSLServer::create(Handle fd) {
            ssl::Socket::create(fd);
            tcp::Server::create(fd);
        }

        void SSLServer::close() {
            Server::close();
            ssl::Socket::close();
        }

        SSLServer::Connection SSLServer::accept() const {
            sockaddr_in addr;
            SocketImpl::SocketLength length = sizeof(addr);

            ohf::Socket::Handle fd = ::accept(ssl::Socket::mFD, (sockaddr *) &addr, &length);
            if (fd == SocketImpl::invalidSocket()) {
                throw Exception(Exception::Code::FAILED_TO_ACCEPT_SOCKET,
                        "Failed to accept socket: " + SocketImpl::getError());
            }

            tcp::SSLSocket *client = new tcp::SSLSocket(context);
            client->create(fd);
            client->accept();

            return {client, InetAddress(*(Uint32 *) &addr.sin_addr), addr.sin_port};
        }

        void SSLServer::bind(const InetAddress &address, Uint16 port) {
            ssl::Socket::create();
            Server::create(ssl::Socket::mFD);

            Server::bind(address, port);
        }
    }
}
