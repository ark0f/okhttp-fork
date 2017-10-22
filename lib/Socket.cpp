//
// Created by Good_Pudge.
//

#include <sstream>
#include "../include/Socket.hpp"
#include "../util/util.hpp"
#include "../include/Exception.hpp"

namespace ohf {
    template class Socket<SocketType::TCP>;
    template class Socket<SocketType::UDP>;

    template <SocketType T>
    int Socket<T>::fd() const {
        return socket_fd;
    }

    template <SocketType T>
    std::iostream &Socket<T>::connect(const HttpURL &url) const {
        int port = url.port();
        if (port == -1)
            throw Exception(Exception::Code::INVALID_PORT, "Invalid port: " + port);
        return connect(url.host(), url.port());
    }

    template <SocketType T>
    void Socket<T>::send(const std::vector<char> &data) const {
        this->send(data.data(), data.size());
    }

    template <SocketType T>
    void Socket<T>::send(const std::string &data) const {
        this->send(data.c_str(), data.length());
    }

    template <SocketType T>
    void Socket<T>::send(std::istream &stream) const {
        std::vector<char> buffer = util::readStream(stream);
        this->send(std::string(buffer.begin(), buffer.end()));
    }

    template <SocketType T>
    std::vector<char> Socket<T>::receiveAll() const {
        std::vector<char> storage;
        std::vector<char> buffer;
        while (!(buffer = receive(512)).empty())
            storage.insert(storage.end(), buffer.begin(), buffer.end());
        return storage;
    }

    template <SocketType T>
    std::string Socket<T>::toString() const {
        std::vector<char> data = receiveAll();
        return std::string(data.begin(), data.end());
    }
}
