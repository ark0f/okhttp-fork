//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSLSOCKET_HPP
#define OKHTTPFORK_SSLSOCKET_HPP

#include "Socket.hpp"
#include <string>
#include <memory>

namespace ohf {
    class SSLSocket : public Socket {
    public:
        enum class Protocol {
            SSLv23,
            SSLv2,
            SSLv3,
            TLSv1,
            TLSv1_1,
            TLSv1_2
        };

        SSLSocket(const Protocol &protocol = Protocol::SSLv23);

        ~SSLSocket();

        std::iostream &connect(const std::string &address, const int &port);

        using Socket::send;

        void send(const char *data, int size);

        std::string receive(size_t size);

    private:
        struct impl;
        impl *pImpl;
    };
}

#endif //OKHTTPFORK_SSLSOCKET_HPP
