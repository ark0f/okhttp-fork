//
// Created by Good_Pudge.
//

#include <sstream>
#include "../include/Socket.hpp"
#include "../include/Exception.hpp"
#include "../util/include/util.hpp"

using namespace ohf;

void Socket::send(const std::string &data) {
    this->send(data.c_str(), data.length());
}

void Socket::send(std::istream &stream) {
    //Read, check and put
    std::string buffer = [&stream]() {
        std::ostringstream oss;
        oss << stream.rdbuf();
        return oss.str();
    }();
    if (stream.bad()) {
        cleanup();
        throw Exception(Exception::Code::FAILED_TO_READ_STREAM, "Failed to read stream: ");
    }
    this->send(buffer);
}

Socket::~Socket() {
    cleanup();
}

#if _WIN32

Socket::Socket() {
    //Init
    WSAData ws; // it really do not use by this class
    if (FAILED(WSAStartup(MAKEWORD(1, 1), &ws)))
        throw Exception(WSAGetLastError(), "Socket error: " + util::getWSAError());
    //Init socket
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
        throw Exception(WSAGetLastError(), "Socket error: " + util::getWSAError());

}

void Socket::cleanup() {
    if (WSACleanup() == SOCKET_ERROR)
        throw Exception(WSAGetLastError(), "Socket error: " + util::getWSAError());
}

std::iostream &Socket::connect(const std::string &address, const int &port) {
    // Address setup
    sockaddr_in addr;
    ZeroMemory(&addr, sizeof(addr));
    addr.sin_family = AF_INET; // TCP/IP
    hostent *hosts = gethostbyname(address.c_str());
    if (hosts) { // found host
        addr.sin_addr.S_un.S_addr = inet_addr(inet_ntoa(**(in_addr **) hosts->h_addr_list)); // Get IP from DNS
    } else throw Exception(WSAGetLastError(), "Socket error: " + util::getWSAError());
    addr.sin_port = htons(port); // Port
    // Connect
    if (::connect(s, (sockaddr *) &addr, sizeof(addr)) == SOCKET_ERROR)
        throw Exception(WSAGetLastError(), "Socket error: " + util::getWSAError());

    // Init IO stream
    buf = std::make_shared<StreamBuf>(this);
    ios = std::make_shared<std::iostream>(buf.get());
    return *ios;
}

void Socket::send(const char *data, int size) {
    if (::send(s, data, size, 0) == SOCKET_ERROR) {
        cleanup();
        throw Exception(WSAGetLastError(), "Socket error: " + util::getWSAError());
    }
}

std::string Socket::receive(size_t size) {
    int len = 0;
    std::string storage;
    char *buffer = new char[size];
    if (size == 0) {
        size = 512;
        do {
            if ((len = recv(s, buffer, size, 0)) == SOCKET_ERROR) {
                cleanup();
                throw Exception(WSAGetLastError(), "Socket error: " + util::getWSAError());
            } else
                storage.append(buffer, len);
        } while (len != 0);
    } else {
        if ((len = recv(s, buffer, size, 0)) == SOCKET_ERROR) {
            cleanup();
            throw Exception(WSAGetLastError(), "Socket error: " + util::getWSAError());
        }
        storage.append(buffer, len);
    }
    return storage;
}

void Socket::disconnect() {
    if (::shutdown(s, 2) == SOCKET_ERROR) { // 2 - SD_BOTH
        cleanup();
        throw Exception(WSAGetLastError(), "Socket error: " + util::getWSAError());
    }
}

#endif

// ohf::Socket::StreamBuf
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

    std::string data = sock->receive(1);
    if (data.empty())
        return traits_type::eof();

    cur = data[0];

    return cur;
}