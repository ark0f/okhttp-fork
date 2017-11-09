//
// Created by Good_Pudge.
//

#include "../include/Socket.hpp"
#include "SocketImpl.hpp"
#include "../include/Exception.hpp"

namespace ohf {
    Socket::Socket(const Type &type) :
            mType(type),
            mFD(SocketImpl::invalidSocket()),
            mBlocking(true),
            mWrite(TimeUnit::ZERO),
            mRead(TimeUnit::ZERO)
    {}

    Socket::Socket() : mWrite(TimeUnit::ZERO), mRead(TimeUnit::ZERO) {}

    Socket::~Socket() {
        close();
    }

    int Socket::fd() const {
        return mFD;
    }

    void Socket::create() {
        if(mFD != SocketImpl::invalidSocket()) return;

        mFD = socket(AF_INET, mType == Type::TCP ? SOCK_STREAM : SOCK_DGRAM, 0);
        if(mFD == SocketImpl::invalidSocket()) {
            throw Exception(Exception::Code::FAILED_TO_CREATE_SOCKET,
                            "Failed to create socket: " + SocketImpl::getError());
        }

        blocking(mBlocking);
    }

    void Socket::blocking(bool mode) {
        if(mFD != SocketImpl::invalidSocket()) {
            SocketImpl::setBlocking(mFD, mode);
        }
        mBlocking = mode;
    }

    bool Socket::isBlocking() const {
        return mBlocking;
    }

    void Socket::close() {
        if(mFD != SocketImpl::invalidSocket()) {
            SocketImpl::close(mFD);
            mFD = SocketImpl::invalidSocket();
        }
    }

    Socket::Socket(const Builder *builder) :
            mType(builder->mType),
            mFD(builder->mFD),
            mBlocking(builder->mBlocking),
            mWrite(builder->mWrite),
            mRead(builder->mRead)
    {}
}