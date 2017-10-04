//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_UTIL_HPP
#define OKHTTPFORK_UTIL_HPP


#include <string>
#include <vector>
#include <ctime>

namespace util {
#if _WIN32
    std::string getWSAError();
#endif

    std::vector<char> readStream(std::istream &stream);

    std::time_t parseDate(const std::string &what, const std::string &format);
    std::string ip2s(const std::vector<unsigned char> &ip);
    std::string getOpenSSLError();
}

#endif //OKHTTPFORK_UTIL_HPP
