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
    class Socket {
    public:
        Socket();

        virtual ~Socket();

        int fd() const;

        virtual std::iostream &connect(const std::string &address, const int &port) const;

        std::iostream &connect(const HttpURL &url) const;

        virtual void send(const char *data, int size) const;

        void send(const std::vector<char> &data) const;

        void send(const std::string &data) const;

        void send(std::istream &stream) const;

        virtual std::vector<char> receive(size_t size) const;

        std::vector<char> receiveAll() const;

        void shutdown(int how = 2) const;

        std::string toString() const;

        friend std::ostream &operator<<(std::ostream &stream, const Socket &socket);
    protected:
        class StreamBuf : public std::streambuf {
        public:
            StreamBuf(Socket *socket);
        protected:
            int overflow(int c) override;

            int uflow() override;

            int underflow() override;

        private:
            Socket *sock;
            int cur;
        };

        std::shared_ptr<std::iostream> ios;
        int socket_fd;
    };
}

#endif //OKHTTPFORK_SOCKET_HPP
