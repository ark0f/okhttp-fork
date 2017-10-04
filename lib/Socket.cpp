//
// Created by Good_Pudge.
//

#include <sstream>
#include "../include/Socket.hpp"
#include "../util/util.hpp"

namespace ohf {
    void Socket::send(const std::vector<char> &data) {
        this->send(data.data(), data.size());
    }

    void Socket::send(const std::string &data) {
        this->send(data.c_str(), data.length());
    }

    void Socket::send(std::istream &stream) {
        std::vector<char> buffer = util::readStream(stream);
        this->send(std::string(buffer.begin(), buffer.end()));
    }

    std::vector<char> Socket::receiveAll() {
        std::vector<char> storage;
        std::vector<char> buffer;
        while (!(buffer = receive(512)).empty())
            storage.insert(storage.end(), buffer.begin(), buffer.end());
        return storage;
    }
}
