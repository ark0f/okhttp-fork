//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_UTIL_HPP
#define OKHTTPFORK_UTIL_HPP


#include <string>
#include <vector>
#include <ctime>
#include <ohf/Config.hpp>

namespace util {
    std::vector<ohf::Int8> readStream(std::istream &stream);

    std::time_t parseDate(const std::string &what, const std::string &format);
}

#endif //OKHTTPFORK_UTIL_HPP
