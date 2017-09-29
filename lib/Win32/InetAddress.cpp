//
// Created by Good_Pudge.
//

#include "../../include/InetAddress.hpp"
#include "../../include/Exception.hpp"
#include "../../util/util.hpp"
#include "WSAInit.hpp"

#include <stdexcept>

namespace ohf {
    WSAInit init;

    InetAddress::InetAddress(const std::string &x) {
        hostent *ips = gethostbyname(x.c_str());
        if (!ips)
            throw Exception(Exception::Code::UNKNOWN_HOST, "Unknown host: " + x);

        mHostName = ips->h_name;

        auto addr = (**(in_addr **) ips->h_addr_list).S_un.S_un_b;
        mIP.push_back(addr.s_b1);
        mIP.push_back(addr.s_b2);
        mIP.push_back(addr.s_b3);
        mIP.push_back(addr.s_b4);
    }

    InetAddress::InetAddress(const std::vector<unsigned char> &ip) : InetAddress(util::ip2s(ip)) {
    }

    std::vector<InetAddress> InetAddress::getAllByName(const std::string &host) {
        hostent *ips = gethostbyname(host.c_str());
        if (!ips)
            throw Exception(Exception::Code::UNKNOWN_HOST, "Unknown host: " + host);

        std::vector<InetAddress> inets;

        in_addr **addresses = (in_addr **) ips->h_addr_list;
        for (int i = 0; addresses[i] != nullptr; i++) {
            auto addr = addresses[i]->S_un.S_un_b;
            InetAddress inetAddress;
            inetAddress.mHostName = ips->h_name;
            inetAddress.mIP.push_back(addr.s_b1);
            inetAddress.mIP.push_back(addr.s_b2);
            inetAddress.mIP.push_back(addr.s_b3);
            inetAddress.mIP.push_back(addr.s_b4);
            inets.push_back(inetAddress);
        }

        return inets;
    }

    std::string InetAddress::hostAddress() {
        return util::ip2s(mIP);
    }
}