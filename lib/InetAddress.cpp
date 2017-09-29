//
// Created by Good_Pudge.
//

#include "../include/InetAddress.hpp"

namespace ohf {
    InetAddress::InetAddress(const char *x) : InetAddress(std::string(x)) {
    }

    std::vector<unsigned char> InetAddress::address() {
        return mIP;
    }

    std::string InetAddress::hostName() {
        return mHostName;
    }
}