//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_UTIL_HPP
#define OKHTTPFORK_UTIL_HPP


#include <string>

namespace util {
#if _WIN32
    std::string getWSAError();
#endif
}

#endif //OKHTTPFORK_UTIL_HPP
