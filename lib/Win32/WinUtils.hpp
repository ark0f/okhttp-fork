//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_WINUTILS_HPP
#define OKHTTPFORK_WINUTILS_HPP

#include <string>

struct WSAInit {
    WSAInit();
    ~WSAInit();
};

std::string getWSAError();

#endif //OKHTTPFORK_WINUTILS_HPP
