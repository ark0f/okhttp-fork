//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_TCP_SSLSOCKET_HPP
#define OKHTTPFORK_TCP_SSLSOCKET_HPP

#include <ohf/ssl/Socket.hpp>
#include <ohf/tcp/Socket.hpp>

namespace ohf {
    namespace tcp {
        class SSLServer;

        class SSLSocket : public tcp::Socket, public ssl::Socket {
        public:
            explicit SSLSocket(const ssl::Context &context, const IO &io = {1024, 1024});

            using tcp::Socket::create;
            void create(Handle handle) override;

            void close() override;

            using tcp::Socket::connect;
            void connect(const InetAddress &address, Uint16 port) override;

            using tcp::Socket::send;
            Int32 send(const char *data, Int32 size) const override;

            using tcp::Socket::receive;
            Int32 receive(char *data, Int32 size) const override;

        private:
            void accept() const;

            friend class ohf::tcp::SSLServer;
        };
    }
}

#endif //OKHTTPFORK_TCP_SSLSOCKET_HPP
