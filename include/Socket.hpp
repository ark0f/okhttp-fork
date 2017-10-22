//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SOCKET_HPP
#define OKHTTPFORK_SOCKET_HPP

#include <streambuf>
#include <string>
#include <memory>
#include <vector>
#include "HttpURL.hpp"

namespace ohf {
    enum class SocketType {
        TCP,
        UDP
    };

    template <SocketType T>
    class Socket {
    public:
        //explicit Socket(const Type &type);
        Socket();

        virtual ~Socket();

        int fd() const;

        virtual std::iostream &connect(const std::string &address, const int &port) const;

        virtual std::iostream &connect(const HttpURL &url) const;

        virtual void send(const char *data, int size) const;

        void send(const std::vector<char> &data) const;

        void send(const std::string &data) const;

        void send(std::istream &stream) const;

        virtual std::vector<char> receive(size_t size) const;

        std::vector<char> receiveAll() const;

        void shutdown(int how = 2) const;

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

        std::shared_ptr<std::iostream> ios;
        int socket_fd;
    };

    using TCPSocket = Socket<SocketType::TCP>;
    using UDPSocket = Socket<SocketType::UDP>;
}

#endif //OKHTTPFORK_SOCKET_HPP
