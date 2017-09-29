//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_UTIL_HPP
#define OKHTTPFORK_UTIL_HPP


#include <string>
#include <vector>

namespace util {
#if _WIN32
    std::string getWSAError();
#endif

    std::string readStream(const std::istream *stream);

    std::string ip2s(const std::vector<unsigned char> &ip);
    std::string getOpenSSLError();
}

#endif //OKHTTPFORK_UTIL_HPP
