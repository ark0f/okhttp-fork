//
// Created by Good_Pudge.
//

#include <ohf/tcp/SSLSocket.hpp>
#include "../SocketImpl.hpp"

namespace ohf {
    namespace tcp {
        SSLSocket::SSLSocket(const ssl::Context &context) :
                ohf::Socket(Type::TCP),
                ssl::Socket(Type::TCP, context)
        {}

        SSLSocket::SSLSocket(SSLSocket &&socket) noexcept :
                tcp::Socket(),
                ssl::Socket(Type::TCP, socket.context)
        {
            mFD = socket.mFD;
            socket.mFD = SocketImpl::invalidSocket();

            mBlocking = socket.mBlocking;
            socket.mBlocking = true;

            mSSL = std::move(socket.mSSL);
        }

        void SSLSocket::connect(const InetAddress &address, Uint16 port) {
            create(address.family());

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

        SSLSocket& SSLSocket::operator =(SSLSocket &&right) noexcept {
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

    void swap(tcp::SSLSocket& a, tcp::SSLSocket& b) {
        swap(a, b);
        swap(a.mSSL, b.mSSL);
    }
}