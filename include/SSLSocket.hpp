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
    template <SocketType T>
    class SSLSocket : public Socket<T> {
    public:
        explicit SSLSocket(const TLSVersion &protocol = TLSVersion::SSLv23);

        ~SSLSocket();

        void sni(const std::string &name);

        using Socket<T>::connect;

        std::iostream &connect(const std::string &address, const int &port) const;

        using Socket<T>::send;

        void send(const char *data, int size) const;

        std::vector<char> receive(size_t size) const;

    private:
        struct impl;
        impl *pImpl; // just for OpenSSL includes

        bool autoSNI;
    };
}

#endif //OKHTTPFORK_SSLSOCKET_HPP
