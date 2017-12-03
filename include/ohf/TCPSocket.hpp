//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_TCPSOCKET_HPP
#define OKHTTPFORK_TCPSOCKET_HPP

#include <iostream>
#include <vector>
#include <memory>
#include "Config.hpp"
#include "HttpURL.hpp"
#include "Socket.hpp"
#include "TimeUnit.hpp"
#include "InetAddress.hpp"

namespace ohf {
    class TCPSocket : public Socket {
    public:
        class Server : public Socket {
        public:
            class Iterator {
            public:
                Iterator(const Server *server);

                TCPSocket operator *() const;

                TCPSocket operator *();

                TCPSocket operator ->() const;

                TCPSocket operator ->();

                const Iterator& operator ++(Int32) const;

                const Iterator& operator ++() const;

                bool operator !=(const Iterator &right) const;

            private:
                const Server *server;
            };

            Server();

            Server(const InetAddress &address, Uint16 port);

            Server(const HttpURL &url);

            void bind(const InetAddress &address, Uint16 port);

            void bind(const HttpURL &url);

            void listen(Int32 count) const;

            void listen() const;

            TCPSocket accept() const;

            const Iterator begin() const;
            Iterator begin();

            const Iterator end() const;
            Iterator end();
        private:

        };

        class Builder : Socket::Builder {
        public:
            Builder();

            Builder& blocking(bool mode);

            Builder& readTimeout(const TimeUnit &unit);

            Builder& writeTimeout(const TimeUnit &unit);

            TCPSocket build();

        private:
            friend class ohf::TCPSocket;
        };

        TCPSocket();

        TCPSocket(const InetAddress &address, Uint16 port);

        TCPSocket(const HttpURL &url);

        virtual void connect(const InetAddress &address, Uint16 port);

        void connect(const HttpURL &url);

        std::iostream& stream() const;

        void disconnect();

        void send(const char *data, size_t size) const;

        void send(const std::vector<Int8> &data) const;

        void send(const std::string &data) const;

        virtual std::vector<Int8> receive(size_t size) const;

        std::string receiveString(size_t size) const;

    private:
        TCPSocket(const Builder *builder);

        std::shared_ptr<std::iostream> mIOS;
    };
}

#endif //OKHTTPFORK_TCPSOCKET_HPP
