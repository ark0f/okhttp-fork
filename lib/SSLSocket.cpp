//
// Created by Good_Pudge.
//

#include <ohf/SSLSocket.hpp>
#include <ohf/Exception.hpp>
#include <cstring>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include "SocketImpl.hpp"

namespace ohf {
    std::string getOpenSSLError() {
        std::string error;
        unsigned long error_code;
        while (error_code = ERR_get_error()) {
            char *str = ERR_error_string(error_code, nullptr);
            if (!str) return error;

            error += str;
        }
        return error;
    }

    Exception checkIO(SSL *ssl, Int32 len) {
        if(len < 0) {
            int error = SSL_get_error(ssl, len);
            if(error != SSL_ERROR_WANT_READ && error != SSL_ERROR_WANT_WRITE) {
                return Exception(Exception::Code::SSL_ERROR, "SSL error: " + getOpenSSLError());
            }
        }
        return Exception(Exception::Code::OK, "OK: ");
    }

    struct ssl_init {
        ssl_init() {
            SSL_library_init();
            SSLeay_add_ssl_algorithms();
            SSL_load_error_strings();
            OpenSSL_add_all_algorithms();
        }

        ~ssl_init() {
            EVP_cleanup();
        }
    };

    ssl_init openssl_init;

    struct SSLSocket::impl {
        SSL *ssl;
        SSL_CTX *context;
    };

    SSLSocket::SSLSocket(const TLSVersion &protocol) : pImpl(new impl), autoSNI(false) {
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

        SSL_CTX *context = SSL_CTX_new(method);
        if(!context) {
            throw Exception(Exception::Code::SSL_CREATE_CONTEXT_ERROR,
                            "SSL context create error: " + getOpenSSLError());
        }
        pImpl->context = context;
    }

    SSLSocket::~SSLSocket() {
        SSL_free(pImpl->ssl);
        SSL_CTX_free(pImpl->context);
        delete pImpl;
    }

    void SSLSocket::sni(const std::string &name) const {
        SSL_set_tlsext_host_name(pImpl->ssl, name.c_str());
        autoSNI = false;
    }

    void SSLSocket::create(Handle fd) {
        if(mFD != SocketImpl::invalidSocket()) return;

        SSL* &ssl = pImpl->ssl;
        // if(ssl != nullptr) SSL_free(ssl);

        TCPSocket::create(fd);

        ssl = SSL_new(pImpl->context);
        if(!ssl) {
            throw Exception(Exception::Code::SSL_CREATE_ERROR,
                            "SSL create error: " + getOpenSSLError());
        }
        SSL_set_fd(ssl, mFD);
    }

    void SSLSocket::connect(const InetAddress &address, Uint16 port) {
        TCPSocket::connect(address, port);

        SSL* &ssl = pImpl->ssl;

        if(autoSNI) SSL_set_tlsext_host_name(ssl, address.hostName().c_str());

        SSL_set_fd(ssl, mFD);
        if(SSL_connect(ssl) <= 0) {
            throw Exception(Exception::Code::SSL_CREATE_CONNECTION_ERROR,
                            "SSL create connection error: " + getOpenSSLError());
        }
    }

    void SSLSocket::send(const char *data, int size) const {
        SSL* &ssl = pImpl->ssl;

        int length = SSL_write(ssl, data, size);
        if(length < 0) {
            int error = SSL_get_error(ssl, length);
            if(error != SSL_ERROR_WANT_READ && error != SSL_ERROR_WANT_WRITE) {
                throw Exception(Exception::Code::SSL_ERROR, "SSL error: " + getOpenSSLError());
            }
        }
    }

    std::vector<Int8> SSLSocket::receive(size_t size) const {
        SSL* &ssl = pImpl->ssl;

        std::vector<Int8> buffer(size);
        int length = SSL_read(ssl, buffer.data(), size);
        if(length < 0) {
            int error = SSL_get_error(ssl, length);
            if(error != SSL_ERROR_WANT_READ && error != SSL_ERROR_WANT_WRITE) {
                throw Exception(Exception::Code::SSL_ERROR, "SSL error: " + getOpenSSLError());
            }
        }

        return std::vector<Int8>(buffer.begin(), buffer.begin() + length);
    }
}
