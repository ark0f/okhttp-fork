//
// Created by Good_Pudge.
//

#include <sstream>
#include "../include/Socket.hpp"
#include "../include/Exception.hpp"
#include "../util/util.hpp"

namespace ohf {
    void Socket::send(const std::string &data) {
        this->send(data.c_str(), data.length());
    }

    void Socket::send(std::istream *stream) {
        std::string buffer = util::readStream(stream);
        if (stream->bad())
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
