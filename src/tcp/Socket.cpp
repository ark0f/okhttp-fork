//
// Created by Good_Pudge.
//

#include "../SocketImpl.hpp"
#include <ohf/tcp/Socket.hpp>
#include <ohf/Exception.hpp>

using namespace std;

#ifdef OKHTTPFORK_UNIX
    #define OHF_FLAGS MSG_NOSIGNAL
#else
    #define OHF_FLAGS 0
#endif


namespace ohf {
    namespace tcp {
        Socket::Socket(StreamBuf *buffer) :
                ohf::Socket(Type::TCP),
                mIOS(make_shared<iostream>(buffer))
        {
            buffer->socket(this);
            mIOS->exceptions(ios::badbit); // rethrow exceptions
        }

        Socket::Socket(tcp::Socket&& socket) noexcept : tcp::Socket() {
            mFD = socket.mFD;
            socket.mFD = SocketImpl::invalidSocket();

            mBlocking = socket.mBlocking;
            socket.mBlocking = true;

            ((StreamBuf *) mIOS->rdbuf())->socket(this);
        }

        void Socket::connect(const InetAddress &address, Uint16 port) {
            create();

            bool is_blocking = isBlocking();
            if (!is_blocking) blocking(true);

            sockaddr_in socket_address = SocketImpl::createAddress(address.toUint32(), port);
            if (::connect(mFD, (sockaddr *) &socket_address, sizeof(sockaddr_in)) == -1) {
                throw Exception(Exception::Code::FAILED_TO_CREATE_CONNECTION,
                        "Failed to create connection: " + SocketImpl::getError());
            }

            blocking(is_blocking);
        }

        void Socket::connect(const HttpURL &url) {
            connect(InetAddress(url.host()), url.port());
        }

        iostream& Socket::stream() const {
            return *mIOS;
        }

        void Socket::disconnect() {
            close();
        }

        Int32 Socket::send(const char *data, Int32 size) const {
            if (!data || size == 0) throw Exception(Exception::Code::NO_DATA_TO_SEND, "No data to send: ");

            Int32 length;
            if ((length = ::send(mFD, data, size, OHF_FLAGS)) < 0) {
                throw Exception(Exception::Code::FAILED_TO_SEND_DATA,
                        "Failed to send data: " + SocketImpl::getError());
            }

            return length;
        }

        Int32 Socket::send(const vector<Int8> &data) const {
            return send(data.data(), data.size());
        }

        Int32 Socket::send(const string &data) const {
            return send(data.data(), data.size());
        }

        Int32 Socket::receive(char *data, Int32 size) const {
            Int32 received = recv(mFD, data, size, OHF_FLAGS);
            if(received < 0) {
                throw Exception(Exception::Code::FAILED_TO_RECEIVE_DATA,
                                "Failed to receive data: " + SocketImpl::getError());
            }
            return received;
        }

        vector<Int8> Socket::receive(Int32 size) const {
            vector<Int8> data(size);
            Int32 received = receive(data.data(), size);
            return {data.begin(), data.begin() + received};
        }

        string Socket::receiveString(Int32 size) const {
            vector<Int8> data = receive(size);
            return {data.begin(), data.end()};
        }

        Socket& Socket::operator =(tcp::Socket&& right) noexcept {
            mFD = right.mFD;
            right.mFD = SocketImpl::invalidSocket();

            mBlocking = right.mBlocking;
            right.mBlocking = true;

            ((StreamBuf *) mIOS->rdbuf())->socket(this);

            return *this;
        }
    }
}

namespace std {
    using namespace ohf;

    void swap(tcp::Socket& a, tcp::Socket& b) {
        std::swap(a.mFD, b.mFD);
        std::swap(a.mBlocking, b.mBlocking);
    }
}
