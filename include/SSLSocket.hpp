//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSLSOCKET_HPP
#define OKHTTPFORK_SSLSOCKET_HPP

#include "TLSVersion.hpp"
#include "TCPSocket.hpp"
#include <vector>
#include <string>
#include <memory>

namespace ohf {
    class SSLSocket : public TCPSocket {
    public:
        explicit SSLSocket(const TLSVersion &protocol = TLSVersion::SSLv23);

        ~SSLSocket();

        void sni(const std::string &name);

        using TCPSocket::connect;

        std::iostream &connect(const std::string &address, Uint16 port);

        using TCPSocket::send;

        void send(const char *data, int size) const;

        std::vector<Int8> receive(size_t size) const;

    private:
        struct impl;
        impl *pImpl; // just for OpenSSL includes

        bool autoSNI;
    };
}

#endif //OKHTTPFORK_SSLSOCKET_HPP
