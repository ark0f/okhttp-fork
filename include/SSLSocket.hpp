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
        SSLSocket();

        ~SSLSocket();

        std::iostream &connect(const std::string &address, const int &port);

        using Socket::send;

        void send(const char *data, int size);

        std::string receive(size_t size = 0);

    private:
        class StreamBuf : public std::streambuf {
        public:
            StreamBuf(SSLSocket *socket) : sock(socket) {};
        protected:
            int overflow(int c) override;

            int uflow() override;

            int underflow() override;

        private:
            SSLSocket *sock;
            int cur;
        };

        std::shared_ptr<StreamBuf> buf;
        SSL *ssl;
        SSL_CTX *ssl_context;
    };
}

#endif //OKHTTPFORK_SSLSOCKET_HPP
