//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_TCP_SSLSOCKET_HPP
#define OKHTTPFORK_TCP_SSLSOCKET_HPP

#include <ohf/ssl/Socket.hpp>
#include <ohf/tcp/Socket.hpp>

namespace ohf {
    namespace tcp {
        class SSLSocket;
    }
}

namespace std {
    void swap(ohf::tcp::SSLSocket& a, ohf::tcp::SSLSocket& b);
}

namespace ohf {
    namespace tcp {
        class SSLServer;

        class SSLSocket : public tcp::Socket, public ssl::Socket {
        public:
            SSLSocket(Family family, const ssl::Context &context, StreamBuf *buffer = new StreamBuf(1024, 1024));

            SSLSocket(SSLSocket&& socket) noexcept;

            using ssl::Socket::create;

            using tcp::Socket::connect;
            void connect(const InetAddress &address, Uint16 port) override;

            using tcp::Socket::send;
            Int32 send(const char *data, Int32 size) const override;

            using tcp::Socket::receive;
            Int32 receive(char *data, Int32 size) const override;

            using ssl::Socket::close;

            SSLSocket& operator =(SSLSocket &&right) noexcept;

        private:
            void accept() const;

            friend void ::std::swap(SSLSocket& a, SSLSocket& b);

            friend class ohf::tcp::SSLServer;
        };
    }
}

#endif //OKHTTPFORK_TCP_SSLSOCKET_HPP
