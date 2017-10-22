//
// Created by Good_Pudge.
//

#include "../include/SSLSocket.hpp"
#include "../include/Exception.hpp"
#include "../util/util.hpp"
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <cstring>

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

namespace ohf {
    struct OpenSSLInit {
        OpenSSLInit() {
            SSL_library_init();
            SSLeay_add_ssl_algorithms();
            SSL_load_error_strings();
        }
    };

    OpenSSLInit globalInitSSL;

    template class SSLSocket<SocketType::TCP>;
    template class SSLSocket<SocketType::UDP>;

    template <SocketType T>
    struct SSLSocket<T>::impl {
        SSL *ssl;
        SSL_CTX *ssl_context;
    };

    template <SocketType T>
    SSLSocket<T>::SSLSocket(const TLSVersion &protocol) :
            Socket<T>(),
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

    template <SocketType T>
    SSLSocket<T>::~SSLSocket() {
        SSL_CTX_free(pImpl->ssl_context);
        SSL_free(pImpl->ssl);
        delete pImpl;
    }

    template <SocketType T>
    void SSLSocket<T>::sni(const std::string &name) {
        SSL_set_tlsext_host_name(pImpl->ssl, name.c_str());
        autoSNI = false;
    }

    template <SocketType T>
    std::iostream &SSLSocket<T>::connect(const std::string &address, const int &port) const {
        std::iostream &ios = Socket<T>::connect(address, port);

        if(autoSNI) SSL_set_tlsext_host_name(pImpl->ssl, address.c_str());

        SSL_set_fd(pImpl->ssl, this->socket_fd);
        if (SSL_connect(pImpl->ssl) < 1)
            throw Exception(Exception::Code::SSL_CONNECTION_CREATE_ERROR,
                            "SSL connection create error: " + getOpenSSLError());

        return ios;
    }

    template <SocketType T>
    void SSLSocket<T>::send(const char *data, int size) const {
        int len = SSL_write(pImpl->ssl, data, size);
        if (len < 0) {
            int error = SSL_get_error(pImpl->ssl, len);
            if (error == SSL_ERROR_WANT_WRITE || error == SSL_ERROR_WANT_READ)
                return;
            throw Exception(Exception::Code::SSL_ERROR, "SSL error: " + getOpenSSLError());
        }
    }

    template <SocketType T>
    std::vector<char> SSLSocket<T>::receive(size_t size) const {
        std::vector<char> buffer(size);
        int len = SSL_read(pImpl->ssl, &buffer.at(0), size);
        if (len < 0) {
            int error = SSL_get_error(pImpl->ssl, len);
            if (error == SSL_ERROR_WANT_WRITE || error == SSL_ERROR_WANT_READ)
                return buffer;
            throw Exception(Exception::Code::SSL_ERROR, "SSL error: " + getOpenSSLError());
        }
        return std::vector<char>(buffer.begin(), buffer.begin() + len);
    }
}
