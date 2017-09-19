//
// Created by Good_Pudge.
//

#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include "../../include/Exception.hpp"
#include "../../include/SSLSocket.hpp"
#include "../../util/include/util.hpp"

namespace ohf {
    std::iostream &SSLSocket::connect(const std::string &address, const int &port) {
        // Address setup
        sockaddr_in addr;
        bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;// TCP/IP
        hostent *hosts = gethostbyname(address.c_str());
        if (!hosts)
            throw Exception(Exception::Code::NO_SUCH_HOST, "No such host: " + address);
        //addr.sin_addr.S_un.S_addr = inet_addr(inet_ntoa(**(in_addr **) hosts->h_addr_list)); // Get IP from DNS
        bcopy(hosts->h_addr,
              (char *) &addr.sin_addr.s_addr,
              hosts->h_length);
        addr.sin_port = htons(port); // Port
        // Connect
        if (::connect(socket_fd, (sockaddr *) &addr, sizeof(addr)) < 0)
            throw Exception(Exception::Code::FAILED_TO_CREATE_CONNECTION, "Failed to create connection: " +
                                                                          std::string(strerror(errno)));
        SSL_set_fd(ssl, socket_fd);
        if (SSL_connect(ssl) < 0)
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

        close(socket_fd);
    }
}
