//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_UDPSOCKET_HPP
#define OKHTTPFORK_UDPSOCKET_HPP

#include "InetAddress.hpp"
#include "Socket.hpp"

namespace ohf {
    class HttpURL;

    class UDPSocket : public Socket {
    public:
        UDPSocket();

        void bind(const InetAddress &address, Uint16 port);

        void unbind();

        void send(const InetAddress &address, Uint16 port, const char *data, size_t size);

        void send(const InetAddress &address, Uint16 port, const std::vector<Int8> &data);

        void send(const InetAddress &address, Uint16 port, const std::string &data);

        size_t receive(InetAddress &address, Uint16 &port, char *data, size_t size);
    private:

    };
}

#endif //OKHTTPFORK_UDPSOCKET_HPP
