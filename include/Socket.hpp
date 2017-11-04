//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SOCKET_HPP
#define OKHTTPFORK_SOCKET_HPP

#include <iostream>
#include <streambuf>
#include <string>
#include <memory>
#include <vector>
#include "HttpURL.hpp"
#include "TimeUnit.hpp"

namespace ohf {
    enum class SocketType {
        TCP,
        UDP
    };

    enum class SocketShutdown {
        RECEIVE, // 0
        SEND,    // 1
        BOTH     // 2
    };

    template <SocketType T>
    class Socket {
    public:
        Socket();

        virtual ~Socket();

        virtual std::iostream &connect(const std::string &address, Uint16 port) const;

        virtual std::iostream &connect(const HttpURL &url) const;

        virtual void send(const char *data, int size) const;

        void send(const std::vector<Int8> &data) const;

        void send(const std::string &data) const;

        void send(std::istream &stream) const;

        virtual std::vector<Int8> receive(size_t size) const;

        std::vector<Int8> receiveAll() const;

        void shutdown(const SocketShutdown &shutdown = SocketShutdown::BOTH) const;

        int fd() const;

        std::string toString() const;

        friend std::ostream &operator<<(std::ostream &stream, const Socket<T> &socket) {
            return stream << socket.toString();
        }
    protected:
        class StreamBuf : public std::streambuf {
        public:
            StreamBuf(Socket<T> *socket);
        protected:
            int overflow(int c) override;

            int uflow() override;

            int underflow() override;

        private:
            Socket<T> *sock;
            int cur;
        };

        std::shared_ptr<std::iostream> mIOStream;
        int mSocketFD;
    private:
        TimeUnit mConnect;
    };

    using TCPSocket = Socket<SocketType::TCP>;
    using UDPSocket = Socket<SocketType::UDP>;
}

#endif //OKHTTPFORK_SOCKET_HPP
