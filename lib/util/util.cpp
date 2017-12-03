//
// Created by Good_Pudge.
//

#include "util.hpp"
#include "../../include/ohf/Exception.hpp"
#include <sstream>
#include <iomanip>

std::vector<ohf::Int8> util::readStream(std::istream &stream) {
    std::vector<ohf::Int8> buffer;
    int c;
    while ((c = stream.get()) != EOF)
        buffer.push_back((char) c);
    if (stream.bad())
        throw ohf::Exception(ohf::Exception::Code::FAILED_TO_READ_STREAM, "Failed to read stream: ");
    return buffer;
}

std::time_t util::parseDate(const std::string &what, const std::string &format) {
    std::tm t{};
    std::istringstream iss(what);
    iss >> std::get_time(&t, format.c_str());
    return std::mktime(&t);
}

std::string util::ip2s(const std::vector<ohf::Uint8> &ip) {
    std::string readyIP;
    for (auto it = ip.begin(); it != ip.end() - 1; it++) {
        readyIP += std::to_string(*it);
        readyIP.push_back('.');
    }
    readyIP += std::to_string(*(ip.end() - 1));

    return readyIP;
}