//
// Created by Good_Pudge.
//

#include "../include/InetAddress.hpp"
#include "../include/Exception.hpp"
#include "../lib/util/util.hpp"

namespace ohf {
    InetAddress::InetAddress(const char *x) : InetAddress(std::string(x)) {
    }

    InetAddress::InetAddress(const std::vector<Uint8> &ip) :
            InetAddress(ip.size() == 4
                        ? util::ip2s(ip)
                        : throw ohf::Exception(ohf::Exception::Code::INVALID_IP, "Invalid IP: "))
    {}

    std::vector<Uint8> InetAddress::address() const {
        return mIP;
    }

    std::string InetAddress::hostAddress() const {
        return util::ip2s(mIP);
    }

    std::string InetAddress::hostName() const {
        return mHostName;
    }

    Uint32 InetAddress::toUint32() const {
        return mIP[0] << 24 | mIP[1] << 16 | mIP[2] << 8 | mIP[3];
    }
}