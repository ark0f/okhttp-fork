//
// Created by Good_Pudge.
//

#include <ohf/InetAddress.hpp>
#include <ohf/Exception.hpp>
#include <cstring>
#include "util/util.hpp"
#include "SocketImpl.hpp"

namespace ohf {
    static SocketImpl::Initializer socket_init;

    InetAddress::InetAddress() : mFamily(Socket::Family::UNKNOWN) {}

    InetAddress::InetAddress(const char *host) : InetAddress(std::string(host)) {}

    InetAddress::InetAddress(const std::string &host, ohf::Int32 af) : InetAddress(getAllByName(host, af)[0]) {}

    InetAddress::InetAddress(const std::string &host, Socket::Family type) : InetAddress(getAllByName(host, type)[0]) {}

    InetAddress::InetAddress(const std::string &host) : InetAddress(getAllByName(host)[0]) {}

    InetAddress::InetAddress(Uint8 b1, Uint8 b2, Uint8 b3, Uint8 b4) :
            mFamily(Socket::Family::IPv4),
            mOriginalType(AF_INET),
            mIP {b1, b2, b3, b4}
    {}

    InetAddress::InetAddress(Uint8 b1, Uint8 b2,  Uint8 b3,  Uint8 b4,  Uint8 b5,  Uint8 b6,  Uint8 b7,  Uint8 b8,
                             Uint8 b9, Uint8 b10, Uint8 b11, Uint8 b12, Uint8 b13, Uint8 b14, Uint8 b15, Uint8 b16) :
            mFamily(Socket::Family::IPv6),
            mOriginalType(AF_INET6),
            mIP {b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15, b16}
    {}

    std::vector<InetAddress> InetAddress::getAllByName(const std::string &host, Int32 af) {
        std::vector<InetAddress> ias;

        addrinfo *info;

        addrinfo hints;
        std::memset(&hints, 0, sizeof(hints));
        hints.ai_flags = AI_CANONNAME;
        hints.ai_family = af;

        if(getaddrinfo(host.c_str(), nullptr, &hints, &info) == 0) {
            for(addrinfo *address = info; address != nullptr; address = address->ai_next) {
                InetAddress inet = SocketImpl::createInetAddress((sockaddr_storage *) address->ai_addr);

                inet.mHostName = host;

                char *canonname = address->ai_canonname;
                if(canonname) inet.mCanonName = canonname;

                ias.push_back(inet);
            }
        } else {
            throw Exception(Exception::Code::UNKNOWN_HOST, "Unknown host: " + host);
        }

        freeaddrinfo(info);

        return ias;
    }

    std::vector<InetAddress> InetAddress::getAllByName(const std::string &host, Socket::Family type) {
        return getAllByName(host, type == Socket::Family::IPv4 ? AF_INET : AF_INET6);
    }

    std::vector<InetAddress> InetAddress::getAllByName(const std::string &host) {
        return getAllByName(host, AF_UNSPEC);
    }

    std::array<Uint8, 16> InetAddress::address() const {
        return mIP;
    }

    std::string InetAddress::hostAddress() const {
        std::string address(45, 0);
        const char *result = inet_ntop(mOriginalType, (void *) mIP.data(), &address[0], address.size());
        address.resize(std::strlen(result));
        return address;
    }

    std::string InetAddress::hostName() const {
        return mHostName;
    }

    std::string InetAddress::canonicalName() const {
        return mCanonName;
    }

    std::vector<std::string> InetAddress::aliases() const {
        return mAliases;
    }

    Socket::Family InetAddress::family() const {
        return mFamily;
    }

    Int32 InetAddress::originalType() const {
        return mOriginalType;
    }

    std::ostream& operator <<(std::ostream &stream, const InetAddress &address) {
        return stream << address.hostAddress();
    }
}