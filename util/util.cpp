//
// Created by Good_Pudge.
//

#include "util.hpp"
#include "../include/Exception.hpp"
#include <openssl/err.h>
#include <sstream>
#include <iomanip>

#if _WIN32

#include <winsock.h>

std::string util::getWSAError() {
    char *error;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  nullptr, WSAGetLastError(),
                  MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
                  (LPSTR) &error, 0, nullptr);
    return std::string(error);
}

#endif

std::vector<char> util::readStream(std::istream &stream) {
    std::vector<char> buffer;
    std::copy(
            std::istreambuf_iterator<char>(stream),
            std::istreambuf_iterator<char>(),
            std::back_inserter(buffer));
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

std::string util::ip2s(const std::vector<unsigned char> &ip) {
    std::string readyIP;
    for (auto it = ip.begin(); it != ip.end() - 1; it++) {
        readyIP += std::to_string(*it);
        readyIP.push_back('.');
    }
    readyIP += std::to_string(*(ip.end() - 1));

    return readyIP;
}

std::string util::getOpenSSLError() {
    std::string error;
    unsigned long error_code;
    while (error_code = ERR_get_error()) {
        char *str = ERR_error_string(error_code, nullptr);
        if (!str)
            return error;
        error += str;
    }
    return error;
}
