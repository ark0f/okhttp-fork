//
// Created by Good_Pudge.
//

#include <ohf/InetAddress.hpp>
#include <ohf/Exception.hpp>
#include <cstring>
#include "util/util.hpp"
#include "SocketImpl.hpp"

namespace ohf {
    InetAddress InetAddress::BROADCAST = InetAddress(INADDR_BROADCAST);
    InetAddress InetAddress::ANY = InetAddress((Uint32) INADDR_ANY);

    std::string ip2s(const std::vector<ohf::Uint8> &ip) {
        std::string readyIP;
        for (auto it = ip.begin(); it != ip.end() - 1; it++) {
            readyIP += std::to_string(*it);
            readyIP.push_back('.');
        }
        readyIP += std::to_string(*(ip.end() - 1));

        return readyIP;
    }

    std::vector<Uint8> uint32tov(Uint32 address) {
        return {
                (Uint8) ((address & 0xFF) >> 0),
                (Uint8) ((address & 0xFF00) >> 8),
                (Uint8) ((address & 0xFF0000) >> 16),
                (Uint8) ((address & 0xFF000000) >> 24)
        };
    }

    SocketImpl::Initializer socket_init;

    InetAddress::InetAddress(const char *x) : InetAddress(std::string(x)) {}

    InetAddress::InetAddress(Uint32 address) : mIP(uint32tov(address)) {}

    InetAddress::InetAddress(const std::string &x) : InetAddress(getAllByName(x)[0]) {}

    InetAddress::InetAddress(const std::vector<Uint8> &ip) :
            InetAddress(ip.size() == 4
                        ? ip2s(ip)
                        : throw ohf::Exception(ohf::Exception::Code::INVALID_IP, "Invalid IP: "))
    {}

    std::vector<InetAddress> InetAddress::getAllByName(const std::string &host) {
        std::vector<InetAddress> ias;

        hostent *hostent = gethostbyname(host.c_str());
        if(hostent) {
            if(hostent->h_addrtype != AF_INET) {
                throw Exception(Exception::Code::INVALID_ADDRESS_TYPE,
                        "Invalid address type: " + std::to_string(hostent->h_addrtype));
            }

            Uint32 *address;
            for(Int32 i = 0; (address = (Uint32 *) hostent->h_addr_list[i]) != nullptr; i++) {
                InetAddress ia;
                ia.mIP = uint32tov(*address);
                ias.push_back(ia);
            }

            // aliases
            std::vector<std::string> aliases;
            const char *alias;
            for(Int32 i = 0; (alias = hostent->h_aliases[i]); i++) {
                aliases.emplace_back(alias);
            }

            for(auto &ia : ias) {
                ia.mHostName = hostent->h_name;
                ia.mAliases = aliases;
            }
        } else {
            throw Exception(Exception::Code::UNKNOWN_HOST, "Unknown host: " + host);
        }

        return ias;
    }

    std::vector<Uint8> InetAddress::address() const {
        return mIP;
    }

    std::string InetAddress::hostAddress() const {
        return ip2s(mIP);
    }

    std::string InetAddress::hostName() const {
        return mHostName;
    }

    std::vector<std::string> InetAddress::aliases() const {
        return mAliases;
    }

    Uint32 InetAddress::toUint32() const {
        return mIP[0] << 24 | mIP[1] << 16 | mIP[2] << 8 | mIP[3];
    }

    std::ostream& operator<<(std::ostream &stream, const InetAddress &address) {
        return stream << address.hostAddress();
    }
}