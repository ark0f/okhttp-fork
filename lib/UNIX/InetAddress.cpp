//
// Created by Good_Pudge.
//

#include "../../include/ohf/InetAddress.hpp"
#include "../../include/ohf/Exception.hpp"
#include "../../lib/util/util.hpp"

#include <stdexcept>
#include <arpa/inet.h>
#include <netdb.h>

namespace ohf {
    InetAddress::InetAddress(const std::string &x) {
        hostent *ips = gethostbyname(x.c_str());
        if (!ips) throw Exception(Exception::Code::UNKNOWN_HOST, "Unknown host: " + x);

        mHostName = ips->h_name;
        auto addr = (**(in_addr **) ips->h_addr_list).s_addr;
        mIP.push_back(addr & 0xFF);
        mIP.push_back((addr & 0xFF00) >> 8);
        mIP.push_back((addr & 0xFF0000) >> 16);
        mIP.push_back((addr & 0xFF000000) >> 24);
    }

    std::vector<InetAddress> InetAddress::getAllByName(const std::string &host) {
        hostent *ips = gethostbyname(host.c_str());
        if (!ips) throw Exception(Exception::Code::UNKNOWN_HOST, "Unknown host: " + host);

        std::vector<InetAddress> inets;

        in_addr **addresses = (in_addr **) ips->h_addr_list;
        for (int i = 0; addresses[i] != nullptr; i++) {
            auto addr = addresses[i]->s_addr;
            inets.emplace_back(std::vector<unsigned char> {
                    (Uint8) (addr & 0xFF),
                    (Uint8) ((addr & 0xFF00) >> 8),
                    (Uint8) ((addr & 0xFF0000) >> 16),
                    (Uint8) ((addr & 0xFF000000) >> 24),
            });
        }

        return inets;
    }
}