//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSLSERVER_HPP
#define OKHTTPFORK_SSLSERVER_HPP

#include <ohf/ssl/Socket.hpp>
#include "Server.hpp"

namespace ohf {
    namespace tcp {
        class SSLServer;
    }
}

namespace std {
    void swap(ohf::tcp::SSLServer& a, ohf::tcp::SSLServer& b);
}

namespace ohf {
    namespace tcp {
        class SSLServer : public Server, public ssl::Socket {
        public:
            explicit SSLServer(const ssl::Context &context);

            SSLServer(SSLServer&& server) noexcept;

            using Server::bind;
            void bind(const InetAddress &address, Uint16 port) override;

            Connection accept() const override;

            SSLServer& operator =(SSLServer&& right) noexcept;

        private:
            friend void ::std::swap(SSLServer& a, SSLServer& b);
        };
    }
}

#endif //OKHTTPFORK_SSLSERVER_HPP
