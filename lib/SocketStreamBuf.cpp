//
// Created by Good_Pudge.
//

#include <vector>
#include <ohf/SocketStreamBuf.hpp>
#include <ohf/TCPSocket.hpp>

namespace ohf {
    SocketStreamBuf::SocketStreamBuf(TCPSocket *socket) : sock(socket), cur(traits_type::eof()) {};

    int SocketStreamBuf::overflow(int c) {
        if (c == traits_type::eof())
            return traits_type::eof();

        char ch = (char) c;
        sock->send(&ch, sizeof(ch));

        return c;
    }

    int SocketStreamBuf::uflow() {
        int c = underflow();
        cur = traits_type::eof();
        return c;
    }

    int SocketStreamBuf::underflow() {
        if (cur != traits_type::eof())
            return cur;

        std::vector<Int8> data = sock->receive(1);
        if (data.empty()) {
            return (cur = traits_type::eof());
        }

        cur = data[0];

        return cur;
    }
}
