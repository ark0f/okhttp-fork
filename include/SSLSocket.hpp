//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSLSOCKET_HPP
#define OKHTTPFORK_SSLSOCKET_HPP

#include "Socket.hpp"
#include "TLSVersion.hpp"
#include <vector>
#include <string>
#include <memory>

namespace ohf {
    class SSLSocket : public Socket {
    public:
        SSLSocket(const TLSVersion &protocol = TLSVersion::SSLv23, const Type &type = Type::TCP);

        ~SSLSocket();

        void sni(const std::string &name) const;

        using Socket::connect;

        std::iostream &connect(const std::string &address, const int &port) const;

        using Socket::send;

        void send(const char *data, int size) const;

        std::vector<char> receive(size_t size) const;

    private:
        struct impl;
        impl *pImpl;
    };
}

#endif //OKHTTPFORK_SSLSOCKET_HPP
