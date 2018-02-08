//
// Created by Good_Pudge.
//

#include <cstring>
#include "SocketImpl.hpp"

namespace ohf {
    SocketImpl::Initializer::Initializer() {
        WSAData data;
        WSAStartup(MAKEWORD(1, 1), &data);
    }

    SocketImpl::Initializer::~Initializer() {
        WSACleanup();
    }

    sockaddr_in SocketImpl::createAddress(Uint32 address, Uint16 port) {
        sockaddr_in sock_addr;
        std::memset(&sock_addr, 0, sizeof(sockaddr_in));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_port = htons(port);
        sock_addr.sin_addr.S_un.S_addr = htonl(address);

        return sock_addr;
    }

    void SocketImpl::close(Socket::Handle sock) {
        closesocket(sock);
    }

    std::string SocketImpl::getError() {
#ifdef UNICODE
        wchar_t *error;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                      nullptr,
                      WSAGetLastError(),
                      MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
                      (LPWSTR) &error,
                      0,
                      nullptr);

        Int32 size = WideCharToMultiByte(CP_UTF8, 0, error, (Int32) wcslen(error), nullptr, 0, nullptr, nullptr);
        std::string str(size, 0);
        WideCharToMultiByte             (CP_UTF8, 0, error, (Int32) wcslen(error), &str[0], size, nullptr, nullptr);
        return str;
#else
        char *error;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                      nullptr,
                      WSAGetLastError(),
                      MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
                      (LPSTR) &error,
                      0,
                      nullptr);
        return error;
#endif
    }

    void SocketImpl::setBlocking(Socket::Handle sock, bool blocking) {
        unsigned long mode = blocking ? 0 : 1;
        ioctlsocket(sock, FIONBIO, &mode);
    }

    Socket::Handle SocketImpl::invalidSocket() {
        return INVALID_SOCKET;
    }
}