//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_WSAINIT_HPP
#define OKHTTPFORK_WSAINIT_HPP

#include <winsock.h>

struct WSAInit {
    WSAInit() {
        WSAData data;
        WSAStartup(MAKEWORD(1, 1), &data);
    }

    ~WSAInit() {
        WSACleanup();
    }
};

#endif //OKHTTPFORK_WSAINIT_HPP
