//
// Created by Good_Pudge.
//

#include <ohf/Socket.hpp>
#include <ohf/Exception.hpp>
#include "SocketImpl.hpp"

namespace ohf {
    Socket::Socket(const Type &type) :
            mType(type),
            mFD(SocketImpl::invalidSocket()),
            mBlocking(true)
    {}

    Socket::~Socket() {
        close();
    }

    Socket::Handle Socket::fd() const {
        return mFD;
    }

    void Socket::create() {
        if(mFD != SocketImpl::invalidSocket()) return;

        Socket::Handle handle = socket(AF_INET, mType == Type::TCP ? SOCK_STREAM : SOCK_DGRAM, 0);
        if(handle == SocketImpl::invalidSocket()) {
            throw Exception(Exception::Code::FAILED_TO_CREATE_SOCKET,
                    "Failed to create socket: " + SocketImpl::getError());
        }
        create(handle);

        blocking(mBlocking);
    }

    void Socket::create(Handle fd) {
        if(mFD == SocketImpl::invalidSocket()) {
            mFD = fd;
        }
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
}