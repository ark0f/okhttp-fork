//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSL_SOCKET_HPP
#define OKHTTPFORK_SSL_SOCKET_HPP

#include <ohf/Socket.hpp>
#include <ohf/InetAddress.hpp>
#include "SSL.hpp"

namespace ohf {
    namespace ssl {
        class Socket : public ohf::Socket {
        public:
            Socket(Type type, const Context &context);

            using ohf::Socket::create;
            void create(Handle fd) override;

            void close() override;

            void sni(bool b);

            void sni(const InetAddress &address);

        protected:
            bool SNICalled;
            const Context &context;
            SSL *ssl;
        };
    }
}

#endif //OKHTTPFORK_SOCKET_HPP
