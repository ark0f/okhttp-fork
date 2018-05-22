//
// Created by Good_Pudge.
//

#include <ohf/tcp/SSLSocket.hpp>
#include "../SocketImpl.hpp"

namespace ohf {
    namespace tcp {
        SSLSocket::SSLSocket(Family family, const ssl::Context &context, StreamBuf *buffer) :
                ohf::Socket(Type::TCP, family),
                tcp::Socket(family, buffer),
                ssl::Socket(Type::TCP, family, context)
        {}

        SSLSocket::SSLSocket(SSLSocket &&socket) noexcept :
                tcp::Socket(socket.mFamily),
                ssl::Socket(Type::TCP, socket.mFamily, socket.context)
        {
            mFD = socket.mFD;
            socket.mFD = SocketImpl::invalidSocket();

            mBlocking = socket.mBlocking;
            socket.mBlocking = true;

            mFamily = socket.mFamily;
            socket.mFamily = Family::UNKNOWN;

            ((StreamBuf *) mIOS->rdbuf())->socket(this);

            mSSL = std::move(socket.mSSL);
        }

        void SSLSocket::connect(const InetAddress &address, Uint16 port) {
            ssl::Socket::create();

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

        SSLSocket& SSLSocket::operator =(SSLSocket &&right) noexcept {
            mFD = right.mFD;
            right.mFD = SocketImpl::invalidSocket();

            mBlocking = right.mBlocking;
            right.mBlocking = true;

            ((StreamBuf *) mIOS->rdbuf())->socket(this);

            mSSL = std::move(right.mSSL);

            return *this;
        }
    }
}

namespace std {
    using namespace ohf;

    void swap(tcp::SSLSocket& a, tcp::SSLSocket& b) {
        swap(a, b);
        swap(a.mSSL, b.mSSL);
    }
}