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
        static const InetAddress EMPTY;

        InetAddress(const char *x);

        explicit InetAddress(const std::string &x);

        explicit InetAddress(const std::vector<Uint8> &ip);

        static std::vector<InetAddress> getAllByName(const std::string &host);

        std::vector<Uint8> address() const;

        std::string hostAddress() const;

        std::string hostName() const;

        Uint32 toUint32() const;

        friend std::ostream& operator<<(std::ostream &stream, const InetAddress &address);
    private:
        InetAddress() = default;

        std::string mHostName;
        std::vector<Uint8> mIP;
    };
}

#endif //OKHTTPFORK_INETADDRESS_HPP
