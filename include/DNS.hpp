//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_DNS_HPP
#define OKHTTPFORK_DNS_HPP

#include <vector>
#include <string>
#include "InetAddress.hpp"

namespace ohf {
    class DNS {
    public:
        virtual std::vector<InetAddress> lookup(const std::string &hostname) = 0;

        class SYSTEM;
    };

    class DNS::SYSTEM : public DNS {
    public:
        std::vector<InetAddress> lookup(const std::string &hostname) override;
    };
}

#endif //OKHTTPFORK_DNS_HPP
