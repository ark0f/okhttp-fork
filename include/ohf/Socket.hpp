//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SOCKET_HPP
#define OKHTTPFORK_SOCKET_HPP

#include "TimeUnit.hpp"

namespace ohf {
    class Socket {
    public:
        #if defined(OKHTTPFORK_WINDOWS)
            #ifdef _WIN64
                typedef Uint64 Handle;
            #else
                typedef Uint32 Handle;
            #endif
        #elif defined(OKHTTPFORK_UNIX)
            typedef Int32 Handle;
        #endif

        enum class Type {
            TCP,
            UDP
        };

        enum class Family {
            UNKNOWN,
            IPv4,
            IPv6
        };

        Socket(Type type);

        virtual ~Socket();

        Handle fd() const;

        virtual void create(Family af);

        virtual void create(Handle fd);

        void blocking(bool mode);

        bool isBlocking() const;

        virtual void close();

        bool isValid() const;

        explicit operator bool();

        Type type() const;

        Family family() const;

    protected:
        Socket() = default;

        Handle mFD;
        bool mBlocking;
        Type mType;
    };

    constexpr Socket::Family IP_UNKNOWN = Socket::Family::UNKNOWN;
    constexpr Socket::Family IPv4 = Socket::Family::IPv4;
    constexpr Socket::Family IPv6 = Socket::Family::IPv6;
}

#endif //OKHTTPFORK_SOCKET_HPP
