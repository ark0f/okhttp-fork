//
// Created by Good_Pudge.
//

#include <ohf/tcp/SSLSocket.hpp>

namespace ohf {
    namespace tcp {
        SSLSocket::SSLSocket(const ssl::Context &context, StreamBuf *buffer) :
                tcp::Socket(buffer),
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

            if(SNICalled) mSSL->setTLSExtHostName(address.hostName());

            tcp::Socket::connect(address, port);
            mSSL->connect();
        }

        Int32 SSLSocket::send(const char *data, Int32 size) const {
            return mSSL->write(data, size);
        }

        Int32 SSLSocket::receive(char *data, Int32 size) const {
            return mSSL->read(data, size);
        }

        void SSLSocket::accept() const {
            mSSL->accept();
        }
    }
}
