//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_UTIL_HPP
#define OKHTTPFORK_UTIL_HPP


#include <string>
#include <vector>
#include <ctime>

namespace util {
    std::vector<char> readStream(std::istream &stream);

    std::time_t parseDate(const std::string &what, const std::string &format);
    std::string ip2s(const std::vector<unsigned char> &ip);
}

#endif //OKHTTPFORK_UTIL_HPP
