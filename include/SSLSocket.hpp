//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSLSOCKET_HPP
#define OKHTTPFORK_SSLSOCKET_HPP

#include "Socket.hpp"
#include <openssl/ssl.h>
#include <string>
#include <memory>

namespace ohf {
    class SSLSocket : public Socket {
    public:
        SSLSocket(const SSL_METHOD *method = SSLv23_method());

        ~SSLSocket();

        std::iostream &connect(const std::string &address, const int &port);

        using Socket::send;

        void send(const char *data, int size);

        std::string receive(size_t size);

    private:
        SSL *ssl;
        SSL_CTX *ssl_context;
    };
}

#endif //OKHTTPFORK_SSLSOCKET_HPP
