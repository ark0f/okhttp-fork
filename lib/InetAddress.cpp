//
// Created by Good_Pudge.
//

#include "../include/InetAddress.hpp"
#include "../include/Exception.hpp"
#include "../util/util.hpp"

namespace ohf {
    InetAddress::InetAddress(const char *x) : InetAddress(std::string(x)) {
    }

    InetAddress::InetAddress(const std::vector<unsigned char> &ip) {
        if (ip.size() != 4)
            throw ohf::Exception(ohf::Exception::Code::INVALID_IP, "Invalid IP: ");
        *this = InetAddress(util::ip2s(ip));
    }

    std::vector<unsigned char> InetAddress::address() {
        return mIP;
    }

    std::string InetAddress::hostAddress() {
        return util::ip2s(mIP);
    }

    std::string InetAddress::hostName() {
        return mHostName;
    }
}