//
// Created by Good_Pudge.
//

#include "../include/Socket.hpp"

using namespace ohf;

int Socket::StreamBuf::overflow(int c) {
    if (c == traits_type::eof())
        return traits_type::eof();

    char ch = (char) c;
    sock->send(&ch, sizeof(ch));

    return c;
}

int Socket::StreamBuf::uflow() {
    int c = underflow();
    cur = traits_type::eof();
    return c;
}

int Socket::StreamBuf::underflow() {
    if (cur != traits_type::eof())
        return cur;

    std::vector<char> data = sock->receive(1);
    if (data.empty())
        return traits_type::eof();

    cur = data[0];

    return cur;
}