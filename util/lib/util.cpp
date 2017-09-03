//
// Created by Good_Pudge.
//


#if _WIN32

#include <winsock.h>
#include "../include/util.hpp"

std::string util::getWSAError() {
    char *error;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  nullptr, WSAGetLastError(),
                  MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
                  (LPSTR) &error, 0, nullptr);
    return std::string(error);
}

#endif