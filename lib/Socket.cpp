//
// Created by Good_Pudge.
//

#include <sstream>
#include "../include/Socket.hpp"
#include "../include/Exception.hpp"

namespace ohf {
    void Socket::send(const std::string &data) {
        this->send(data.c_str(), data.length());
    }

    void Socket::send(std::istream &stream) {
        //Read, check and put
        std::string buffer = [&stream]() {
            std::ostringstream oss;
            oss << stream.rdbuf();
            return oss.str();
        }();
        if (stream.bad())
            throw Exception(Exception::Code::FAILED_TO_READ_STREAM, "Failed to read stream: ");
        this->send(buffer);
    }

    std::string Socket::receiveAll() {
        std::string storage;
        std::string buffer;
        while (!(buffer = receive(512)).empty())
            storage.append(buffer);
        return storage;
    }
}
