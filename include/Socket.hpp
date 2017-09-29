//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SOCKET_HPP
#define OKHTTPFORK_SOCKET_HPP

#include <streambuf>
#include <string>
#include <memory>

namespace ohf {
    class Socket {
    public:
        Socket();

        virtual ~Socket();

        virtual std::iostream &connect(const std::string &address, const int &port);

        virtual void send(const char *data, int size);

        void send(const std::string &data);

        void send(std::istream *stream);

        virtual std::string receive(size_t size);

        std::string receiveAll();

        void shutdown(int how = 2);

    protected:
        class StreamBuf : public std::streambuf {
        public:
            StreamBuf(Socket *socket) : sock(socket), cur(traits_type::eof()) {};
        protected:
            int overflow(int c) override;

            int uflow() override;

            int underflow() override;

        private:
            Socket *sock;
            int cur;
        };

        std::shared_ptr<StreamBuf> buf;
        std::shared_ptr<std::iostream> ios;
        int socket_fd;
    };
}

#endif //OKHTTPFORK_SOCKET_HPP
