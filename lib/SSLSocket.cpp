//
// Created by Good_Pudge.
//

#include "../include/SSLSocket.hpp"
#include "../include/Exception.hpp"
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <cstring>

namespace ohf {
    std::string getOpenSSLError() {
        std::string error;
        unsigned long error_code;
        while (error_code = ERR_get_error()) {
            char *str = ERR_error_string(error_code, nullptr);
            if (!str)
                return error;
            error += str;
        }
        return error;
    }

    struct OpenSSLInit {
        OpenSSLInit() {
            SSL_library_init();
            SSLeay_add_ssl_algorithms();
            SSL_load_error_strings();
        }
    };

    OpenSSLInit globalSSLInit;

    struct SSLSocket::impl {
        SSL *ssl;
        SSL_CTX *ssl_context;
    };

    SSLSocket::SSLSocket(const TLSVersion &protocol) :
            TCPSocket(),
            pImpl(new impl),
            autoSNI(true)
    {
        const SSL_METHOD *method;
        switch (protocol) {
            case TLSVersion::SSLv23:
                method = SSLv23_method();
                break;
            case TLSVersion::SSLv3:
                method = SSLv3_method();
                break;
            case TLSVersion::TLSv1:
                method = TLSv1_method();
                break;
            case TLSVersion::TLSv1_1:
                method = TLSv1_1_method();
                break;
            case TLSVersion::TLSv1_2:
                method = TLSv1_2_method();
                break;
        }

        pImpl->ssl_context = SSL_CTX_new(method);
        if (!pImpl->ssl_context)
            throw Exception(Exception::Code::SSL_CONTEXT_CREATE_ERROR,
                            "SSL context create error:" + getOpenSSLError());

        pImpl->ssl = SSL_new(pImpl->ssl_context);
        if (!pImpl->ssl)
            throw Exception(Exception::Code::SSL_CREATE_ERROR, "SSL create error: " + getOpenSSLError());
    }

    SSLSocket::~SSLSocket() {
        SSL_CTX_free(pImpl->ssl_context);
        SSL_free(pImpl->ssl);
        delete pImpl;
    }

    void SSLSocket::sni(const std::string &name) {
        SSL_set_tlsext_host_name(pImpl->ssl, name.c_str());
        autoSNI = false;
    }

    std::iostream &SSLSocket::connect(const std::string &address, Uint16 port) {
        std::iostream &ios = TCPSocket::connect(address, port);

        if(autoSNI) SSL_set_tlsext_host_name(pImpl->ssl, address.c_str());

        SSL_set_fd(pImpl->ssl, mFD);
        if (SSL_connect(pImpl->ssl) < 1)
            throw Exception(Exception::Code::SSL_CONNECTION_CREATE_ERROR,
                            "SSL connection create error: " + getOpenSSLError());

        return ios;
    }

    void SSLSocket::send(const char *data, int size) const {
        int len = SSL_write(pImpl->ssl, data, size);
        if (len < 0) {
            int error = SSL_get_error(pImpl->ssl, len);
            if (error == SSL_ERROR_WANT_WRITE || error == SSL_ERROR_WANT_READ)
                return;
            throw Exception(Exception::Code::SSL_ERROR, "SSL error: " + getOpenSSLError());
        }
    }

    std::vector<Int8> SSLSocket::receive(size_t size) const {
        std::vector<Int8> buffer(size);
        int len = SSL_read(pImpl->ssl, &buffer.at(0), size);
        if (len < 0) {
            int error = SSL_get_error(pImpl->ssl, len);
            if (error == SSL_ERROR_WANT_WRITE || error == SSL_ERROR_WANT_READ)
                return buffer;
            throw Exception(Exception::Code::SSL_ERROR, "SSL error: " + getOpenSSLError());
        }
        return std::vector<Int8>(buffer.begin(), buffer.begin() + len);
    }
}
