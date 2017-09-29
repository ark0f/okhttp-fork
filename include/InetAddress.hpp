//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_INETADDRESS_HPP
#define OKHTTPFORK_INETADDRESS_HPP

#include <string>
#include <vector>

namespace ohf {
    class InetAddress {
    public:
        InetAddress() = default;

        InetAddress(const char *x);

        InetAddress(const std::string &x);

        InetAddress(const std::vector<unsigned char> &ip);

        static std::vector<InetAddress> getAllByName(const std::string &host);

        std::vector<unsigned char> address();

        std::string hostAddress();

        std::string hostName();

    private:
        std::string mHostName;
        std::vector<unsigned char> mIP;
    };
}

#endif //OKHTTPFORK_INETADDRESS_HPP
