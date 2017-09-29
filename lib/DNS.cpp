//
// Created by Good_Pudge.
//

#include "../include/DNS.hpp"

namespace ohf {
    std::vector<InetAddress> DNS::SYSTEM::lookup(const std::string &hostname) {
        return InetAddress::getAllByName(hostname);
    }
}