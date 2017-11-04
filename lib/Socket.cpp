//
// Created by Good_Pudge.
//

#include <sstream>
#include "../include/Socket.hpp"
#include "../lib/util/util.hpp"
#include "../include/Exception.hpp"
#include "SocketImpl.hpp"
#include "../include/InetAddress.hpp"

namespace ohf {
    template class Socket<SocketType::TCP>;
    template class Socket<SocketType::UDP>;

    template <SocketType T>
    Socket<T>::Socket() :
            mConnect(TimeUnit::ZERO),
            mIOStream(std::make_shared<std::iostream>(new StreamBuf(this)))
    {
        int type, protocol;
        if(T == SocketType::TCP) {
            type = SOCK_STREAM;
            protocol = IPPROTO_TCP;
        } else {
            type = SOCK_DGRAM;
            protocol = IPPROTO_UDP;
        }

        if((mSocketFD = socket(AF_INET, type, protocol)) == SocketImpl::invalidSocket()) {
            throw Exception(Exception::Code::FAILED_TO_CREATE_SOCKET,
                            "Failed to create socket: " + SocketImpl::getError());
        }
    }

    template <SocketType T>
    Socket<T>::~Socket() {
        SocketImpl::close(mSocketFD);
    }

    template <SocketType T>
    std::iostream& Socket<T>::connect(const std::string &address, Uint16 port) const {
        sockaddr_in addr = SocketImpl::createAddress(InetAddress(address).toUint32(), port);
        if(::connect(mSocketFD, (sockaddr *) &addr, sizeof(sockaddr)) == -1) {
            throw Exception(Exception::Code::FAILED_TO_CREATE_CONNECTION,
                            "Failed to create connection: " + SocketImpl::getError());
        }
        return *mIOStream;
    }

    template <SocketType T>
    std::iostream &Socket<T>::connect(const HttpURL &url) const {
        return connect(url.host(), url.port());
    }

    template <SocketType T>
    void Socket<T>::send(const char *data, int size) const {
        if(::send(mSocketFD, data, size, 0) == -1) {
            throw Exception(Exception::Code::FAILED_TO_SEND_DATA,
                            "Failed to send data: " + SocketImpl::getError());
        }
    }

    template <SocketType T>
    void Socket<T>::send(const std::vector<Int8> &data) const {
        this->send(data.data(), data.size());
    }

    template <SocketType T>
    void Socket<T>::send(const std::string &data) const {
        this->send(data.c_str(), data.length());
    }

    template <SocketType T>
    void Socket<T>::send(std::istream &stream) const {
        std::vector<Int8> buffer = util::readStream(stream);
        this->send(std::string(buffer.begin(), buffer.end()));
    }

    template <SocketType T>
    std::vector<Int8> Socket<T>::receive(size_t size) const {
        std::vector<Int8> buffer(size);
        int received = 0;
        if((received = ::recv(mSocketFD, buffer.data(), size, 0)) == -1) {
            throw Exception(Exception::Code::FAILED_TO_RECEIVE_DATA,
                            "Failed to receive data: " + SocketImpl::getError());
        }
        return std::vector<Int8>(buffer.begin(), buffer.begin() + received);
    }

    template <SocketType T>
    std::vector<Int8> Socket<T>::receiveAll() const {
        std::vector<Int8> storage;
        std::vector<Int8> buffer;
        while (!(buffer = receive(512)).empty())
            storage.insert(storage.end(), buffer.begin(), buffer.end());
        return storage;
    }

    template <SocketType T>
    void Socket<T>::shutdown(const SocketShutdown &shutdown) const {
        if(::shutdown(mSocketFD, static_cast<int>(shutdown)) == -1) {
            throw Exception(Exception::Code::FAILED_TO_SHUTDOWN_SOCKET,
                            "Failed to shutdown socket: " + SocketImpl::getError());
        }
    }

    template <SocketType T>
    int Socket<T>::fd() const {
        return mSocketFD;
    }

    template <SocketType T>
    std::string Socket<T>::toString() const {
        std::vector<Int8> data = receiveAll();
        return std::string(data.begin(), data.end());
    }
}
