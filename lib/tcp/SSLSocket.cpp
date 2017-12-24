//
// Created by Good_Pudge.
//

#include <ohf/tcp/SSLSocket.hpp>

namespace ohf {
    namespace tcp {
        SSLSocket::SSLSocket(const ssl::Context &context, const IO &io) :
                tcp::Socket(io),
                ssl::Socket(Type::TCP, context)
        {}

        void SSLSocket::create(Handle fd) {
            ssl::Socket::create(fd);
            tcp::Socket::create(fd);
        }

        void SSLSocket::close() {
            tcp::Socket::close();
            ssl::Socket::close();
        }

        void SSLSocket::connect(const InetAddress &address, Uint16 port) {
            ssl::Socket::create();
            tcp::Socket::create(ssl::Socket::mFD);

            tcp::Socket::connect(address, port);
            ssl->connect();
        }

        Int32 SSLSocket::send(const char *data, Int32 size) const {
            return ssl->write(data, size);
        }

        Int32 SSLSocket::receive(char *data, Int32 size) const {
            return ssl->read(data, size);
        }

        void SSLSocket::accept() const {
            ssl->accept();
        }
    }
}
