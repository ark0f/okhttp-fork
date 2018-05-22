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

        Socket(Type type, Family family);

        virtual ~Socket();

        Handle fd() const;

        virtual void create();

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
        Family mFamily;
    };
}

#endif //OKHTTPFORK_SOCKET_HPP
