//
// Created by Good_Pudge.
//

#include "../SocketImpl.hpp"
#include <ohf/tcp/Socket.hpp>
#include <ohf/Exception.hpp>

using namespace std;

namespace ohf {
    namespace tcp {
        Socket::Socket(const IO &io) :
                ohf::Socket(Type::TCP),
                mIOS(make_shared<iostream>(new StreamBuf(io, this)))
        {
            mIOS->exceptions(ios::badbit); // rethrow exceptions
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
            if ((length = ::send(mFD, data, size, 0)) < 0) {
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
            Int32 received = recv(mFD, data, size, 0);
            if(received < 0) {
                throw Exception(Exception::Code::FAILED_TO_RECEIVE_DATA,
                                "Failed to receive data: " + SocketImpl::getError());
            }
            return received;
        }

        vector<Int8> Socket::receive(Int32 size) const {
            vector<Int8> data(size);
            receive(data.data(), size);
            return data;
        }

        string Socket::receiveString(Int32 size) const {
            vector<Int8> data = receive(size);
            return string(data.begin(), data.end());
        }
    }
}
