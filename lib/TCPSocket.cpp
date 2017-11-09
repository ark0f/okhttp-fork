//
// Created by Good_Pudge.
//

#include "SocketImpl.hpp"
#include "../include/TCPSocket.hpp"
#include "../include/HttpURL.hpp"
#include "../include/SocketStreamBuf.hpp"
#include "../include/Exception.hpp"
#include "../include/InetAddress.hpp"
#include "../include/TimeUnit.hpp"

using namespace std;

namespace ohf {
    TCPSocket::TCPSocket() :
            Socket(Socket::Type::TCP),
            mIOS(make_shared<iostream>(new SocketStreamBuf(this)))
    {
        create();
    }

    TCPSocket::TCPSocket(const Builder *builder) :
            Socket(builder),
            mIOS(make_shared<iostream>(new SocketStreamBuf(this)))
    {}

    iostream& TCPSocket::connect(const string &address, Uint16 port) {
        create();

        bool is_blocking = isBlocking();
        if(!is_blocking)
            blocking(true);

        sockaddr_in socket_address = SocketImpl::createAddress(InetAddress(address).toUint32(), port);
        if(::connect(mFD, (sockaddr *) &socket_address, sizeof(sockaddr_in)) == -1) {
            throw Exception(Exception::Code::FAILED_TO_CREATE_CONNECTION,
                            "Failed to create connection: " + SocketImpl::getError());
        }

        blocking(is_blocking);

        return *mIOS;
    }

    iostream& TCPSocket::connect(const HttpURL &url) {
        return connect(url.host(), url.port());
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
        int len = recv(mFD, data.data(), size, 0);
        if(len > 0)
            return vector<Int8>(data.begin(), data.begin() + len);
        else if(len == 0)
            return vector<Int8>();

        throw Exception(Exception::Code::FAILED_TO_RECEIVE_DATA,
                        "Failed to receive data: " + SocketImpl::getError());
    }

    string TCPSocket::receiveString(size_t size) const {
        vector<Int8> data = receive(size);
        return string(data.begin(), data.end());
    }

    vector<Int8> TCPSocket::receiveAll(size_t bufferSize) const {
        vector<Int8> storage;
        vector<Int8> part;
        while(!(part = receive(bufferSize)).empty()) {
            storage.insert(storage.end(), part.begin(), part.end());
        }
        return storage;
    }

    string TCPSocket::receiveAllString() const {
        vector<Int8> data = receiveAll();
        return string(data.begin(), data.end());
    }

    ostream& operator<<(ostream &stream, const TCPSocket &socket) {
        return stream << socket.receiveAllString();
    }
}
