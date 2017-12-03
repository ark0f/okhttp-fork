//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SOCKETSTREAMBUF_HPP
#define OKHTTPFORK_SOCKETSTREAMBUF_HPP

#include <streambuf>

namespace ohf {
    class TCPSocket;

    class SocketStreamBuf : public std::streambuf {
    public:
        explicit SocketStreamBuf(TCPSocket *socket);

    protected:
        int overflow(int c) override;

        int uflow() override;

        int underflow() override;

    private:
        TCPSocket *sock;
        int cur;
    };
}

#endif //OKHTTPFORK_SOCKETSTREAMBUF_HPP
