//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSLSOCKET_HPP
#define OKHTTPFORK_SSLSOCKET_HPP

#include "Socket.hpp"
#include <vector>
#include <string>
#include <memory>

namespace ohf {
    class SSLSocket : public Socket {
    public:
        enum class Protocol {
            SSLv23,
            SSLv3,
            TLSv1,
            TLSv1_1,
            TLSv1_2
        };

        SSLSocket(const Protocol &protocol = Protocol::SSLv23);

        ~SSLSocket();

        void sni(const std::string &name);

        std::iostream &connect(const std::string &address, const int &port);

        using Socket::send;

        void send(const char *data, int size);

        std::vector<char> receive(size_t size);

    private:
        struct impl;
        impl *pImpl;
    };
}

#endif //OKHTTPFORK_SSLSOCKET_HPP
