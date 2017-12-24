//
// Created by Good_Pudge.
//

#include <ohf/DNS.hpp>

namespace ohf {
    std::vector<InetAddress> DNS::SYSTEM::lookup(const std::string &hostname) {
        return InetAddress::getAllByName(hostname);
    }
}