//
// Created by Good_Pudge.
//

#include <ohf/tcp/Socket.hpp>

namespace ohf {
    namespace tcp {
        Socket::StreamBuf::StreamBuf(Int32 write, Int32 read) : IOStreamBuf(write, read) {}

        void Socket::StreamBuf::socket(tcp::Socket *socket) {
            mSocket = socket;
        }

        Int32 Socket::StreamBuf::write(const char *data, Int32 length) {
            return mSocket->send(data, length);
        }

        Int32 Socket::StreamBuf::read(char *data, Int32 length) {
            return mSocket->receive(data, length);
        }
    }
}