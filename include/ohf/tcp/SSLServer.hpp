//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSLSERVER_HPP
#define OKHTTPFORK_SSLSERVER_HPP

#include <ohf/ssl/Socket.hpp>
#include "Server.hpp"

namespace ohf {
    namespace tcp {
        class SSLServer : public Server, public ssl::Socket {
        public:
            explicit SSLServer(const ssl::Context &context);

            using Server::create;
            void create(Handle fd) override;

            void close() override;

            using Server::bind;
            void bind(const InetAddress &address, Uint16 port) override;

            Connection accept() const override;

        private:

        };
    }
}

#endif //OKHTTPFORK_SSLSERVER_HPP
