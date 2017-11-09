//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_TCPSOCKET_HPP
#define OKHTTPFORK_TCPSOCKET_HPP

#include <iostream>
#include <vector>
#include <memory>
#include "Config.hpp"
#include "Socket.hpp"
#include "TimeUnit.hpp"

namespace ohf {
    class HttpURL;

    class TCPSocket : public Socket {
    public:
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

        virtual std::iostream& connect(const std::string &address, Uint16 port);

        std::iostream& connect(const HttpURL &url);

        void disconnect();

        void send(const char *data, size_t size) const;

        void send(const std::vector<Int8> &data) const;

        void send(const std::string &data) const;

        virtual std::vector<Int8> receive(size_t size) const;

        std::string receiveString(size_t size) const;

        std::vector<Int8> receiveAll(size_t bufferSize = 512) const;

        std::string receiveAllString() const;

        friend std::ostream& operator <<(std::ostream &stream, const TCPSocket &socket);
    private:
        TCPSocket(const Builder *builder);

        std::shared_ptr<std::iostream> mIOS;
    };
}

#endif //OKHTTPFORK_TCPSOCKET_HPP
