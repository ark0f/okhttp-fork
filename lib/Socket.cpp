//
// Created by Good_Pudge.
//

#include <sstream>
#include "../include/Socket.hpp"
#include "../util/util.hpp"
#include "../include/Exception.hpp"

namespace ohf {
    int Socket::fd() const {
        return socket_fd;
    }

    std::iostream &Socket::connect(const HttpURL &url) const {
        int port = url.port();
        if (port == -1)
            throw Exception(Exception::Code::INVALID_PORT, "Invalid port: " + port);
        return connect(url.host(), url.port());
    }

    void Socket::send(const std::vector<char> &data) const {
        this->send(data.data(), data.size());
    }

    void Socket::send(const std::string &data) const {
        this->send(data.c_str(), data.length());
    }

    void Socket::send(std::istream &stream) const {
        std::vector<char> buffer = util::readStream(stream);
        this->send(std::string(buffer.begin(), buffer.end()));
    }

    std::vector<char> Socket::receiveAll() const {
        std::vector<char> storage;
        std::vector<char> buffer;
        while (!(buffer = receive(512)).empty())
            storage.insert(storage.end(), buffer.begin(), buffer.end());
        return storage;
    }

    std::string Socket::toString() const {
        std::vector<char> data = receiveAll();
        return std::string(data.begin(), data.end());
    }

    std::ostream &operator<<(std::ostream &stream, const Socket &socket) {
        stream << socket.toString();
        return stream;
    }
}
