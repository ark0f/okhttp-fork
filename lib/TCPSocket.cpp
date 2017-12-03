//
// Created by Good_Pudge.
//

#include "SocketImpl.hpp"
#include <ohf/TCPSocket.hpp>
#include <ohf/SocketStreamBuf.hpp>
#include <ohf/Exception.hpp>

using namespace std;

namespace ohf {
    TCPSocket::TCPSocket() :
            Socket(Socket::Type::TCP),
            mIOS(make_shared<iostream>(new SocketStreamBuf(this)))
    {}

    TCPSocket::TCPSocket(const InetAddress &address, Uint16 port) : TCPSocket() {
        connect(address, port);
    }

    TCPSocket::TCPSocket(const HttpURL &url) : TCPSocket() {
        connect(url);
    }

    TCPSocket::TCPSocket(const Builder *builder) :
            Socket(builder),
            mIOS(make_shared<iostream>(new SocketStreamBuf(this)))
    {}

    void TCPSocket::connect(const InetAddress &address, Uint16 port) {
        create();

        bool is_blocking = isBlocking();
        if(!is_blocking) blocking(true);

        sockaddr_in socket_address = SocketImpl::createAddress(address.toUint32(), port);
        if(::connect(mFD, (sockaddr *) &socket_address, sizeof(sockaddr_in)) == -1) {
            throw Exception(Exception::Code::FAILED_TO_CREATE_CONNECTION,
                            "Failed to create connection: " + SocketImpl::getError());
        }

        blocking(is_blocking);
    }

    void TCPSocket::connect(const HttpURL &url) {
        connect(InetAddress(url.host()), url.port());
    }

    iostream& TCPSocket::stream() const {
        return *mIOS;
    }

    void TCPSocket::disconnect() {
        close();
    }

    void TCPSocket::send(const char *data, size_t size) const {
        if(!data || size == 0) throw Exception(Exception::Code::NO_DATA_TO_SEND, "No data to send: ");

        if(::send(mFD, data, size, 0) < 0) {
            throw Exception(Exception::Code::FAILED_TO_SEND_DATA, "Failed to send data: " + SocketImpl::getError());
        }
    }

    void TCPSocket::send(const vector<Int8> &data) const {
        send(data.data(), data.size());
    }

    void TCPSocket::send(const string &data) const {
        send(data.data(), data.size());
    }

    vector<Int8> TCPSocket::receive(size_t size) const {
        vector<Int8> data(size);
        Int32 received = recv(mFD, data.data(), size, 0);
        if(received > 0)
            return vector<Int8>(data.begin(), data.begin() + received);
        else if(received == 0)
            return vector<Int8>();

        throw Exception(Exception::Code::FAILED_TO_RECEIVE_DATA,
                        "Failed to receive data: " + SocketImpl::getError());
    }

    string TCPSocket::receiveString(size_t size) const {
        vector<Int8> data = receive(size);
        return string(data.begin(), data.end());
    }
}
