//
// Created by Good_Pudge.
//

#include "../include/SSLSocket.hpp"

using namespace ohf;

int SSLSocket::StreamBuf::overflow(int c) {
    if (c == traits_type::eof())
        return traits_type::eof();

    char ch = (char) c;
    sock->send(&ch, 1);

    return c;
}

int SSLSocket::StreamBuf::uflow() {
    int c = underflow();
    cur = traits_type::eof();
    return c;
}

int SSLSocket::StreamBuf::underflow() {
    if (cur != traits_type::eof())
        return cur;

    std::string data = sock->receive(1);
    if (data.empty())
        return traits_type::eof();

    cur = data[0];

    return cur;
}