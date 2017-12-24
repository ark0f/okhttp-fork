//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_INETADDRESS_HPP
#define OKHTTPFORK_INETADDRESS_HPP

#include <string>
#include <vector>
#include "Config.hpp"

namespace ohf {
    class InetAddress {
    public:
        static InetAddress BROADCAST;
        static InetAddress ANY;

        InetAddress() = default;

        InetAddress(Uint32 address);

        InetAddress(const char *x);

        explicit InetAddress(const std::string &x);

        explicit InetAddress(const std::vector<Uint8> &ip);

        static std::vector<InetAddress> getAllByName(const std::string &host);

        std::vector<Uint8> address() const;

        std::string hostAddress() const;

        std::string hostName() const;

        std::vector<std::string> aliases() const;

        Uint32 toUint32() const;

        friend std::ostream& operator<<(std::ostream &stream, const InetAddress &address);

    private:
        std::string mHostName;
        std::vector<std::string> mAliases;
        std::vector<Uint8> mIP;
    };
}

#endif //OKHTTPFORK_INETADDRESS_HPP
