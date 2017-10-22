//
// Created by Good_Pudge.
//

#include "../include/Socket.hpp"

namespace ohf {
    template class Socket<SocketType::TCP>;
    template class Socket<SocketType::UDP>;

    template <SocketType T>
    Socket<T>::StreamBuf::StreamBuf(Socket<T> *socket) : sock(socket), cur(traits_type::eof()) {};

    template <SocketType T>
    int Socket<T>::StreamBuf::overflow(int c) {
        if (c == traits_type::eof())
            return traits_type::eof();

        char ch = (char) c;
        sock->send(&ch, sizeof(ch));

        return c;
    }

    template <SocketType T>
    int Socket<T>::StreamBuf::uflow() {
        int c = underflow();
        cur = traits_type::eof();
        return c;
    }

    template <SocketType T>
    int Socket<T>::StreamBuf::underflow() {
        if (cur != traits_type::eof())
            return cur;

        std::vector<char> data = sock->receive(1);
        if (data.empty())
            return traits_type::eof();

        cur = data[0];

        return cur;
    }
}
