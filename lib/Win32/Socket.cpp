//
// Created by Good_Pudge.
//

#include "../../util/util.hpp"
#include "../../include/Exception.hpp"
#include "../../include/Socket.hpp"
#include "WSAInit.hpp"
#include "../../include/InetAddress.hpp"
#include <iostream>

std::string getWSAError() {
    char *error;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  nullptr, WSAGetLastError(),
                  MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
                  (LPSTR) &error, 0, nullptr);
    return std::string(error);
}

namespace ohf {
    template class Socket<SocketType::TCP>;
    template class Socket<SocketType::UDP>;

    template <SocketType T>
    Socket<T>::Socket() : ios(std::make_shared<std::iostream>(new StreamBuf(this)))
    {
        int s_type, protocol;
        if(T == SocketType::TCP) {
            s_type = SOCK_STREAM;
            protocol = IPPROTO_TCP;
        } else if(T == SocketType::UDP) {
            s_type = SOCK_DGRAM;
            protocol = IPPROTO_UDP;
        }

        if ((socket_fd = socket(AF_INET, s_type, protocol)) == INVALID_SOCKET)
            throw Exception(Exception::Code::FAILED_TO_CREATE_SOCKET,
                            "Failed to create socket: " + getWSAError());
    }

    template <SocketType T>
    Socket<T>::~Socket() {
        closesocket(socket_fd);
    }

    template <SocketType T>
    std::iostream &Socket<T>::connect(const std::string &address, const int &port) const {
        // Address setup
        sockaddr_in addr;
        ZeroMemory(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.S_un.S_addr = inet_addr(InetAddress(address).hostAddress().c_str());
        addr.sin_port = htons(port);
        // Connect
        if (::connect(socket_fd, (sockaddr *) &addr, sizeof(addr)) == SOCKET_ERROR)
            throw Exception(Exception::Code::FAILED_TO_CREATE_CONNECTION,
                            "Failed to create connection: " + getWSAError());

        return *ios;
    }

    template <SocketType T>
    void Socket<T>::send(const char *data, int size) const {
        if (::send(socket_fd, data, size, 0) == SOCKET_ERROR)
            throw Exception(Exception::Code::FAILED_TO_SEND_DATA, "Failed to send data: " + getWSAError());
    }

    template <SocketType T>
    std::vector<char> Socket<T>::receive(size_t size) const {
        int len = 0;
        std::vector<char> buffer(size);
        if ((len = recv(socket_fd, &buffer.at(0), size, 0)) == SOCKET_ERROR)
            throw Exception(Exception::Code::FAILED_TO_RECEIVE_DATA, "Failed to receive data: " + getWSAError());
        return std::vector<char>(buffer.begin(), buffer.begin() + len);
    }

    template <SocketType T>
    void Socket<T>::shutdown(int how) const {
        if (::shutdown(socket_fd, how) == SOCKET_ERROR)
            throw Exception(Exception::Code::FAILED_TO_SHUTDOWN_SOCKET,
                            "Failed to shutdown socket: " + getWSAError());
    }
}
