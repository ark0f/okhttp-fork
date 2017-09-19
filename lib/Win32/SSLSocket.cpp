//
// Created by Good_Pudge.
//

#include "../../util/include/util.hpp"
#include "../../include/SSLSocket.hpp"
#include "../../include/Exception.hpp"
#include <iostream>

namespace ohf {
    std::iostream &SSLSocket::connect(const std::string &address, const int &port) {
        // Address setup
        sockaddr_in addr;
        ZeroMemory(&addr, sizeof(addr));
        addr.sin_family = AF_INET; // TCP/IP
        hostent *hosts = gethostbyname(address.c_str());
        if (!hosts) // host not found
            throw Exception(Exception::Code::NO_SUCH_HOST, "No such host: " + address);
        addr.sin_addr.S_un.S_addr = inet_addr(inet_ntoa(**(in_addr **) hosts->h_addr_list)); // Get IP from DNS
        addr.sin_port = htons(port); // Port
        // Connect
        if (::connect(socket_fd, (sockaddr *) &addr, sizeof(addr)) == SOCKET_ERROR)
            throw Exception(Exception::Code::FAILED_TO_CREATE_CONNECTION, "Failed to create connection: " +
                                                                          util::getWSAError());

        SSL_set_fd(ssl, socket_fd);
        if (SSL_connect(ssl) < 1)
            throw Exception(Exception::Code::FAILED_TO_CREATE_SSL_CONNECTION,
                            "Failed to create SSL connection: " + util::getOpenSSLError());

        // Init IO stream
        buf = std::make_shared<StreamBuf>(this);
        ios = std::make_shared<std::iostream>(buf.get());
        return *ios;
    }

    SSLSocket::~SSLSocket() {
        SSL_CTX_free(ssl_context);
        SSL_free(ssl);

        closesocket(socket_fd);
    }
}
