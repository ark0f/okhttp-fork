//
// Created by Good_Pudge.
//

#include "../SocketImpl.hpp"
#include <ohf/udp/Socket.hpp>
#include <ohf/HttpURL.hpp>

namespace ohf {
    namespace udp {
        Socket::Socket() : ohf::Socket(Type::UDP) {}

        Socket::Socket(udp::Socket&& socket) noexcept : udp::Socket() {
            mFD = socket.mFD;
            socket.mFD = SocketImpl::invalidSocket();

            mBlocking = socket.mBlocking;
            socket.mBlocking = true;
        }

        void Socket::bind(const InetAddress &address, Uint16 port) {
            create(address.family());
            mFamily = address.family();

            SocketImpl::SocketLength length;
            sockaddr_storage socket_address = SocketImpl::createAddress(address, port, length);
            if (::bind(mFD, (sockaddr *) &socket_address, length) == -1) {
                throw Exception(Exception::Code::FAILED_TO_BIND_SOCKET,
                                "Failed to bind socket: " + SocketImpl::getError());
            }
        }

        void Socket::unbind() {
            close();
        }

        void Socket::send(const InetAddress &address, Uint16 port, const char *data, Int32 size) {
            if (!data || size == 0) throw Exception(Exception::Code::NO_DATA_TO_SEND, "No data to send: ");
            if (size > 65507) {
                throw Exception(Exception::Code::DATAGRAM_PACKET_IS_TOO_BIG,
                                "Datagram packet is too big: " + std::to_string(size));
            }

            SocketImpl::SocketLength length;
            sockaddr_storage socket_address = SocketImpl::createAddress(address, port, length);
            if (::sendto(mFD, data, size, 0, (sockaddr *) &socket_address, length) < 0) {
                throw Exception(Exception::Code::FAILED_TO_SEND_DATA, "Failed to send data: " + SocketImpl::getError());
            }
        }

        void Socket::send(const InetAddress &address, Uint16 port, const std::vector<Int8> &data) {
            send(address, port, data.data(), data.size());
        }

        void Socket::send(const InetAddress &address, Uint16 port, const std::string &data) {
            send(address, port, data.data(), data.size());
        }

        Int32 Socket::receive(InetAddress &address, Uint16 &port, char *data, Int32 size) {
            SocketImpl::SocketLength length;

            InetAddress inet;
            switch(mFamily) {
                case Family::IPv4: inet = ipv4::ANY; break;
                case Family::IPv6: inet = ipv6::ANY; break;
                default:
                    throw Exception(Exception::Code::INVALID_ADDRESS_TYPE,
                                    "Invalid address type: " + std::to_string((int) mFamily));
            }

            sockaddr_storage socket_address = SocketImpl::createAddress(inet, 0, length);

            Int32 dataReceived = recvfrom(mFD, data, size, 0, (sockaddr *) &socket_address, &length);
            if (dataReceived < 0) {
                throw Exception(Exception::Code::FAILED_TO_RECEIVE_DATA,
                                "Failed to receive data: " + SocketImpl::getError());
            }

            address = SocketImpl::createInetAddress(&socket_address);
            port = SocketImpl::port(&socket_address);

            return dataReceived;
        }

        Int32 Socket::receive(InetAddress &address, Uint16 &port, std::vector<Int8> &data, Int32 size) {
            data.clear();
            data.resize(size);
            Int32 received = receive(address, port, data.data(), size);
            data.resize(received);
            data.shrink_to_fit();
            return received;
        }

        Int32 Socket::receive(InetAddress &address, Uint16 &port, std::string &data, Int32 size) {
            data.clear();
            data.resize(size);
            Int32 received = receive(address, port, &data[0], size);
            data.resize(received);
            data.shrink_to_fit();
            return received;
        }

        Socket& Socket::operator =(udp::Socket &&right) noexcept {
            mFD = right.mFD;
            right.mFD = SocketImpl::invalidSocket();

            mBlocking = right.mBlocking;
            right.mBlocking = true;

            return *this;
        }
    }
}

namespace std {
    using namespace ohf;

    void swap(ohf::udp::Socket& a, ohf::udp::Socket& b) {
        swap(a.mFD, b.mFD);
        swap(a.mBlocking, b.mBlocking);
    }
}
