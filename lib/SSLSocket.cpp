//
// Created by Good_Pudge.
//

#include "../include/SSLSocket.hpp"
#include "../include/Exception.hpp"
#include "../util/include/util.hpp"

namespace ohf {
    namespace priv {
        struct OpenSSLInit {
            OpenSSLInit() {
                SSL_library_init();
                SSLeay_add_ssl_algorithms();
                SSL_load_error_strings();
            }
        };

        OpenSSLInit globalInitSSL;
    }

    SSLSocket::SSLSocket(const SSL_METHOD *method) : Socket() {
        ssl_context = SSL_CTX_new(method);
        if (!ssl_context)
            throw Exception(Exception::Code::OPENSSL_CREATE_CONTEXT_ERROR, "OpenSSL create context error:" +
                                                                           util::getOpenSSLError());

        ssl = SSL_new(ssl_context);
        if (!ssl)
            throw Exception(Exception::Code::OPENSSL_INIT_ERROR, "OpenSSL init error: " +
                                                                 util::getOpenSSLError());
    }

    void SSLSocket::send(const char *data, int size) {
        int len = SSL_write(ssl, data, size);
        if (len < 0) {
            int error = SSL_get_error(ssl, len);
            if (error == SSL_ERROR_WANT_WRITE || error == SSL_ERROR_WANT_READ)
                return;
            throw Exception(Exception::Code::OPENSSL_ERROR, util::getOpenSSLError());
        }
    }

    std::string SSLSocket::receive(size_t size) {
        char *buffer = new char[size];
        int len = SSL_read(ssl, buffer, size);
        if (len < 0) {
            int error = SSL_get_error(ssl, len);
            if (error == SSL_ERROR_WANT_WRITE || error == SSL_ERROR_WANT_READ)
                return std::string(buffer, len);
            throw Exception(Exception::Code::OPENSSL_ERROR, util::getOpenSSLError());
        }
        return std::string(buffer, len);
    }
}
