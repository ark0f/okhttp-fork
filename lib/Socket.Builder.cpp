//
// Created by Good_Pudge.
//

#include "SocketImpl.hpp"
#include "../include/Socket.hpp"
#include "../include/Exception.hpp"

namespace ohf {
    Socket::Builder::Builder(const Socket::Type &type) :
            mType(type),
            mBlocking(false),
            mWrite(TimeUnit::ZERO),
            mRead(TimeUnit::ZERO)
    {
        mFD = socket(AF_INET, type == Socket::Type::TCP ? SOCK_STREAM : SOCK_DGRAM, 0);
        if(mFD == SocketImpl::invalidSocket()) {
            throw Exception(Exception::Code::FAILED_TO_CREATE_SOCKET,
                            "Failed to create socket: " + SocketImpl::getError());
        }

        blocking(mBlocking);
    }

    Socket::Builder& Socket::Builder::blocking(bool mode) {
        SocketImpl::setBlocking(mFD, mode);
        mBlocking = mode;
        return *this;
    }

    Socket::Builder& Socket::Builder::readTimeout(const TimeUnit &unit) {
        mRead = unit;
        timeval tv = {
                unit.sec(),
                unit.usec()
        };
        setsockopt(mFD, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof(tv));
        return *this;
    }

    Socket::Builder& Socket::Builder::writeTimeout(const TimeUnit &unit) {
        mWrite = unit;
        timeval tv = {
                unit.sec(),
                unit.usec()
        };
        setsockopt(mFD, SOL_SOCKET, SO_SNDTIMEO, (const char *) &tv, sizeof(tv));
        return *this;
    }

    Socket Socket::Builder::build() const {
        return {this};
    }
}