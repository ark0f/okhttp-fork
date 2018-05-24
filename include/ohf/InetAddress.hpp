//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_INETADDRESS_HPP
#define OKHTTPFORK_INETADDRESS_HPP

#include <string>
#include <array>
#include <vector>
#include "Config.hpp"
#include "Socket.hpp"

namespace ohf {
    class InetAddress {
    public:
        InetAddress();

        InetAddress(const char *host);

        InetAddress(const std::string &host, Int32 af);

        InetAddress(const std::string &host, Socket::Family type);

        explicit InetAddress(const std::string &host);

        InetAddress(Uint8 b1, Uint8 b2, Uint8 b3, Uint8 b4);

        InetAddress(Uint8 b1, Uint8 b2,  Uint8 b3,  Uint8 b4,  Uint8 b5,  Uint8 b6,  Uint8 b7,  Uint8 b8,
                    Uint8 b9, Uint8 b10, Uint8 b11, Uint8 b12, Uint8 b13, Uint8 b14, Uint8 b15, Uint8 b16);

        static std::vector<InetAddress> getAllByName(const std::string &host, Int32 af);

        static std::vector<InetAddress> getAllByName(const std::string &host, Socket::Family family);

        static std::vector<InetAddress> getAllByName(const std::string &host);

        std::array<Uint8, 16> address() const;

        std::string hostAddress() const;

        std::string hostName() const;

        std::string canonicalName() const;

        Socket::Family family() const;

        Int32 originalType() const;

        friend std::ostream& operator <<(std::ostream &stream, const InetAddress &address);

    private:
        std::string mHostName;
        std::string mCanonName;
        std::array<Uint8, 16> mIP;

        Socket::Family mFamily;
        Int32 mOriginalType;
    };

    namespace ipv4 {
        static InetAddress BROADCAST = {255, 255, 255, 255};
        static InetAddress ANY = {0, 0, 0, 0};
        static InetAddress LOCALHOST = {127, 0, 0, 1};
    }

    namespace ipv6 {
        static InetAddress BROADCAST = {255, 255, 255, 255, 255, 255, 255, 255,
                                        255, 255, 255, 255, 255, 255, 255, 255};
        static InetAddress ANY = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        static InetAddress LOCALHOST = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    }
}

#endif //OKHTTPFORK_INETADDRESS_HPP
