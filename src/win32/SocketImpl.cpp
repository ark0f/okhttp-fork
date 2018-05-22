//
// Created by Good_Pudge.
//

#include "SocketImpl.hpp"
#include <cstring>

namespace ohf {
    namespace SocketImpl {
        Initializer::Initializer() {
            WSAData data;
            WSAStartup(MAKEWORD(1, 1), &data);
        }

        Initializer::~Initializer() {
            WSACleanup();
        }

        void close(Socket::Handle sock) {
            closesocket(sock);
        }

        std::string getError() {
            wchar_t *error;
            FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                           nullptr,
                           WSAGetLastError(),
                           MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                           (LPWSTR) &error,
                           0,
                           nullptr);

            std::wstring werror(error);
            int size = WideCharToMultiByte(CP_UTF8, 0, &werror[0], werror.size(), nullptr, 0, nullptr, nullptr);
            std::string aerror(size, 0);
            WideCharToMultiByte(CP_UTF8, 0, &werror[0], werror.size(), &aerror[0], size, NULL, NULL);

            return aerror;
        }

        void setBlocking(Socket::Handle sock, bool blocking) {
            unsigned long mode = blocking ? 0 : 1;
            ioctlsocket(sock, FIONBIO, &mode);
        }

        Socket::Handle invalidSocket() {
            return INVALID_SOCKET;
        }
    }
}
