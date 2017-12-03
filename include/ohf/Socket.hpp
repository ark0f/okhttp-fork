//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SOCKET_HPP
#define OKHTTPFORK_SOCKET_HPP

#include "TimeUnit.hpp"

namespace ohf {
    class TCPSocket;
    class UDPSocket;

    class Socket {
    public:
        #if defined(OKHTTPFORK_WINDOWS)
            typedef unsigned int Handle;
        #elif defined(OKHTTPFORK_UNIX)
            typedef int Handle;
        #endif

        enum class Type {
            TCP,
            UDP
        };

        class Builder {
        public:
            explicit Builder(const Socket::Type &type);

            virtual Builder& blocking(bool mode);

            virtual Builder& readTimeout(const TimeUnit &unit);

            virtual Builder& writeTimeout(const TimeUnit &unit);

            virtual Socket build() const;

        private:
            Handle mFD;
            bool mBlocking;
            Socket::Type mType;
            TimeUnit mRead;
            TimeUnit mWrite;

            friend class ohf::Socket;

            friend class ohf::TCPSocket;
            friend class ohf::UDPSocket;
        };

        explicit Socket(const Type &type);

        virtual ~Socket();

        Handle fd() const;

        virtual void create();

        virtual void create(Handle fd);

        void blocking(bool mode);

        bool isBlocking() const;

        virtual void close();

    protected:
        Handle mFD;
        bool mBlocking;
        Type mType;
        TimeUnit mRead;
        TimeUnit mWrite;

        friend class ohf::TCPSocket;
        friend class ohf::UDPSocket;

        Socket();
        Socket(const Builder *builder);
    };
}

#endif //OKHTTPFORK_SOCKET_HPP
