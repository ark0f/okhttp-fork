//
// Created by Good_Pudge.
//

#include "../../include/InetAddress.hpp"
#include "../../include/Exception.hpp"
#include "WinUtils.hpp"

#include <stdexcept>
#include <winsock.h>

namespace ohf {
    WSAInit init;

    InetAddress::InetAddress(const std::string &x) {
        hostent *ips = gethostbyname(x.c_str());
        if (!ips) throw Exception(Exception::Code::UNKNOWN_HOST, "Unknown host: " + x);

        mHostName = ips->h_name;

        auto addr = (**(in_addr **) ips->h_addr_list).S_un.S_un_b;
        mIP.push_back(addr.s_b1);
        mIP.push_back(addr.s_b2);
        mIP.push_back(addr.s_b3);
        mIP.push_back(addr.s_b4);
    }

    std::vector<InetAddress> InetAddress::getAllByName(const std::string &host) {
        hostent *ips = gethostbyname(host.c_str());
        if (!ips) throw Exception(Exception::Code::UNKNOWN_HOST, "Unknown host: " + host);

        std::vector<InetAddress> inets;

        in_addr **addresses = (in_addr **) ips->h_addr_list;
        for (int i = 0; addresses[i] != nullptr; i++) {
            auto addr = addresses[i]->S_un.S_un_b;
            inets.emplace_back(std::vector<unsigned char> {
                addr.s_b1,
                addr.s_b2,
                addr.s_b3,
                addr.s_b4
            });
        }

        return inets;
    }
}