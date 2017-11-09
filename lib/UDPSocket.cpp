//
// Created by Good_Pudge.
//

#include "SocketImpl.hpp"
#include "../include/UDPSocket.hpp"
#include "../include/Exception.hpp"

namespace ohf {
    UDPSocket::UDPSocket() : Socket(Type::UDP) {
        create();
    }

    void UDPSocket::bind(const InetAddress &address, Uint16 port) {
        create();

        sockaddr_in socket_address = SocketImpl::createAddress(address.toUint32(), port);
        if(::bind(mFD, (sockaddr *) &socket_address, sizeof(sockaddr_in)) == -1) {
            throw Exception(Exception::Code::FAILED_TO_BIND_SOCKET,
                            "Failed to bind socket: " + SocketImpl::getError());
        }
    }

    void UDPSocket::unbind() {
        close();
    }

    void UDPSocket::send(const InetAddress &address, Uint16 port, const char *data, size_t size) {
        if(!data || size == 0) throw Exception(Exception::Code::NO_DATA_TO_SEND, "No data to send: ");
        if(size > 65507) throw Exception(Exception::Code::DATAGRAM_PACKET_IS_TOO_BIG, "Datagram packet is too big: ");

        sockaddr_in socket_address = SocketImpl::createAddress(address.toUint32(), port);
        if(::sendto(mFD, data, size, 0, (sockaddr *) &socket_address, sizeof(sockaddr_in)) < 0) {
            throw Exception(Exception::Code::FAILED_TO_SEND_DATA, "Failed to send data: " + SocketImpl::getError());
        }
    }

    void UDPSocket::send(const InetAddress &address, Uint16 port, const std::vector<Int8> &data) {
        send(address, port, data.data(), data.size());
    }

    void UDPSocket::send(const InetAddress &address, Uint16 port, const std::string &data) {
        send(address, port, data.data(), data.size());
    }

    size_t UDPSocket::receive(InetAddress &address, Uint16 &port, char *data, size_t size) {
        sockaddr_in socket_address = SocketImpl::createAddress(INADDR_ANY, 0);
        SocketImpl::SocketLength addressSize = sizeof(sockaddr_in);
        Int32 dataReceived = recvfrom(mFD, data, size, 0, (sockaddr *) &socket_address, (socklen_t *) &addressSize);
        if(dataReceived < 0) {
            throw Exception(Exception::Code::FAILED_TO_RECEIVE_DATA,
                            "Failed to receive data: " + SocketImpl::getError());
        }

        address = inet_ntoa(socket_address.sin_addr);
        port = ntohs(socket_address.sin_port);

        return static_cast<size_t>(dataReceived);
    }
}