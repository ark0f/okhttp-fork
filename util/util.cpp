//
// Created by Good_Pudge.
//

#include "util.hpp"
#include <openssl/err.h>
#include <sstream>

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

std::string util::readStream(const std::istream *stream) {
    std::ostringstream oss;
    oss << stream->rdbuf();
    return oss.str();
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
