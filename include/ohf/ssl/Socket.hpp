//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSL_SOCKET_HPP
#define OKHTTPFORK_SSL_SOCKET_HPP

#include <ohf/Socket.hpp>
#include <ohf/InetAddress.hpp>
#include <memory>
#include "SSL.hpp"

namespace ohf {
    namespace ssl {
        class Socket : public virtual ohf::Socket {
        public:
            Socket(Type type, Family family, const Context &context);

            using ohf::Socket::create;
            void create(Handle fd) override;

            void close() override;

            void sni(bool b);

            void sni(const InetAddress &address);

            bool isSNI() const;

            const SSL &ssl() const;
        protected:
            bool SNICalled;
            const Context &context;
            std::shared_ptr<SSL> mSSL;
        };
    }
}

#endif //OKHTTPFORK_SOCKET_HPP
