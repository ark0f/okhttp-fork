//
// Created by Good_Pudge.
//

#include <ohf/TCPSocket.hpp>

namespace ohf {
    TCPSocket::Builder::Builder() : Socket::Builder(Type::TCP) {}

    TCPSocket::Builder& TCPSocket::Builder::blocking(bool mode) {
        Socket::Builder::blocking(mode);
        return *this;
    }

    TCPSocket::Builder& TCPSocket::Builder::readTimeout(const TimeUnit &unit) {
        Socket::Builder::readTimeout(unit);
        return *this;
    }

    TCPSocket::Builder& TCPSocket::Builder::writeTimeout(const TimeUnit &unit) {
        Socket::Builder::writeTimeout(unit);
        return *this;
    }

    TCPSocket TCPSocket::Builder::build() {
        return {this};
    }
}