//
// Created by Good_Pudge.
//

#include "WinUtils.hpp"

#include <winsock.h>

WSAInit::WSAInit() {
    WSAData data;
    WSAStartup(MAKEWORD(1, 1), &data);
}

WSAInit::~WSAInit() {
    WSACleanup();
}

std::string getWSAError() {
    char *error;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  nullptr, WSAGetLastError(),
                  MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
                  (LPSTR) &error, 0, nullptr);
    return std::string(error);
}