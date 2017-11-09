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
            int mFD;
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

        int fd() const;

        void create();

        void blocking(bool mode);

        bool isBlocking() const;

        void close();

    protected:
        int mFD;
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
