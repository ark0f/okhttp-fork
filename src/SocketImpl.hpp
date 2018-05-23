//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SOCKETIMPL_HPP
#define OKHTTPFORK_SOCKETIMPL_HPP

#include <ohf/Config.hpp>
#include <ohf/Exception.hpp>
#include <ohf/InetAddress.hpp>
#include <cstring>

#if defined(OKHTTPFORK_WINDOWS)
    #include "win32/SocketImpl.hpp"
#elif defined(OKHTTPFORK_UNIX)
    #include "unix/SocketImpl.hpp"
#endif

namespace ohf {
    namespace SocketImpl {
        static Socket::Family family(Socket::Handle fd) {
            SocketLength length = sizeof(sockaddr);
            sockaddr addr;
            std::memset(&addr, 0, length);

            if(getsockname(fd, &addr, &length) == -1) {
                throw Exception(Exception::Code::FAILED_TO_GET_SOCKET_NAME,
                                "Failed to get socket name: " + getError());
            }

            Int32 af = addr.sa_family;
            Socket::Family family;
            switch(af) {
                case AF_INET: family = Socket::Family::IPv4;
                case AF_INET6: family = Socket::Family::IPv6;
                default:
                    throw Exception(Exception::Code::INVALID_ADDRESS_TYPE,
                                    "Invalid address type: " + std::to_string(af));
            }

            return family;
        }

        static sockaddr_storage createAddress(const InetAddress &address, Uint16 port, SocketLength &length) {
            sockaddr_storage sock_addr;

            Int32 family = address.originalType();
            switch (family) {
                case AF_INET: {
                    std::memset(&sock_addr, 0, sizeof(sockaddr_in));
                    auto ipv4 = ((sockaddr_in *) &sock_addr);
                    ipv4->sin_family = AF_INET;
                    ipv4->sin_port = htons(port);
                    std::memcpy(&ipv4->sin_addr, address.address().data(), sizeof(in_addr));
                    length = sizeof(sockaddr_in);
                    break;
                }
                case AF_INET6: {
                    std::memset(&sock_addr, 0, sizeof(sockaddr_in6));
                    auto ipv6 = ((sockaddr_in6 *) &sock_addr);
                    ipv6->sin6_family = AF_INET6;
                    ipv6->sin6_port = htons(port);
                    std::memcpy(&ipv6->sin6_addr, address.address().data(), sizeof(in6_addr));
                    length = sizeof(sockaddr_in6);
                    break;
                }
                default:
                    throw Exception(Exception::Code::INVALID_ADDRESS_TYPE,
                                    "Invalid address type: " + std::to_string(family));
            }

            return sock_addr;
        }

        static Uint16 port(sockaddr_storage *addr) {
            Uint16 port = 0;
            Int32 family = addr->ss_family;
            switch (family) {
                case AF_INET:
                    port = ((sockaddr_in *) addr)->sin_port;
                    break;
                case AF_INET6:
                    port = ((sockaddr_in6 *) addr)->sin6_port;
                    break;
                default:
                    throw Exception(Exception::Code::INVALID_ADDRESS_TYPE,
                                    "Invalid address type: " + std::to_string(family));
            }
            return ntohs(port);
        }

        static InetAddress createInetAddress(sockaddr_storage *addr) {
            InetAddress inet;

            int family = addr->ss_family;
            switch (family) {
                case AF_INET: {
                    auto ip = (Uint8 *) &((sockaddr_in *) addr)->sin_addr;
                    inet = InetAddress(ip[0], ip[1], ip[2], ip[3]);
                    break;
                }
                case AF_INET6: {
                    auto ip = (Uint8 *) &((sockaddr_in6 *) addr)->sin6_addr;
                    inet = InetAddress(ip[0], ip[1], ip[2], ip[3], ip[4], ip[5], ip[6], ip[7],
                                           ip[8], ip[9], ip[10], ip[11], ip[12], ip[13], ip[14], ip[15]);
                    break;
                }
                default:
                    throw Exception(Exception::Code::INVALID_ADDRESS_TYPE,
                                    "Invalid address type: " + std::to_string(family));
            }

            return inet;
        }

        static SocketLength addressLength(Socket::Family type) {
            SocketLength length;
            switch(type) {
                case Socket::Family::IPv4: length = sizeof(sockaddr_in); break;
                case Socket::Family::IPv6: length = sizeof(sockaddr_in6); break;
                case Socket::Family::UNKNOWN:
                    throw Exception(Exception::Code::INVALID_FAMILY_TYPE,
                                    "Invalid ohf::InetAddress type: " + std::to_string((int) type));
            }
            return length;
        }
    }
}

#endif // OKHTTPFORK_SOCKETIMPL_HPP
