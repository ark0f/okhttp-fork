//
// Created by Good_Pudge.
//

#include <ohf/InetAddress.hpp>
#include <ohf/Exception.hpp>
#include <cstring>
#include "util/util.hpp"
#include "SocketImpl.hpp"

namespace {
    std::string ip2s(const std::vector<ohf::Uint8> &ip) {
        std::string readyIP;
        for (auto it = ip.begin(); it != ip.end() - 1; it++) {
            readyIP += std::to_string(*it);
            readyIP.push_back('.');
        }
        readyIP += std::to_string(*(ip.end() - 1));

        return readyIP;
    }

    std::vector<ohf::Uint8> uint32tov(ohf::Uint32 address) {
        return {
                (ohf::Uint8) ((address & 0xFF) >> 0),
                (ohf::Uint8) ((address & 0xFF00) >> 8),
                (ohf::Uint8) ((address & 0xFF0000) >> 16),
                (ohf::Uint8) ((address & 0xFF000000) >> 24)
        };
    }
}

namespace ohf {
    InetAddress InetAddress::BROADCAST = InetAddress(INADDR_BROADCAST);
    InetAddress InetAddress::ANY = InetAddress((Uint32) INADDR_ANY);

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

        addrinfo hints;
        std::memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_flags = AI_CANONNAME;

        addrinfo *info;
        if(getaddrinfo(host.c_str(), nullptr, &hints, &info) == 0 && info) {
            std::string canon_name = info->ai_canonname;
            for(; info != nullptr; info = info->ai_next) {
                Uint32 address = *(Uint32 *) &reinterpret_cast<sockaddr_in *>(info->ai_addr)->sin_addr;

                InetAddress inet;
                inet.mHostName = host;
                inet.mCanonName = canon_name;
                inet.mIP = uint32tov(address);

                ias.push_back(inet);
            }

            freeaddrinfo(info);
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

    std::string InetAddress::canonicalName() const {
        return mCanonName;
    }

    Uint32 InetAddress::toUint32() const {
        return mIP[0] << 24 | mIP[1] << 16 | mIP[2] << 8 | mIP[3];
    }

    std::ostream& operator <<(std::ostream &stream, const InetAddress &address) {
        return stream << address.hostAddress();
    }
}