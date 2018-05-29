//
// Created by Good_Pudge.
//

#include <ohf/tcp/Socket.hpp>

namespace ohf {
    namespace tcp {
        Socket::Stream::Stream(Socket &socket, Socket::StreamBuf *buffer) : std::iostream(buffer) {
            buffer->socket(&socket);
            exceptions(std::ios::badbit); // rethrow exceptions
        }

        void Socket::Stream::socket(Socket &socket) {
            ((StreamBuf *) rdbuf())->socket(&socket);
        }
    }
}