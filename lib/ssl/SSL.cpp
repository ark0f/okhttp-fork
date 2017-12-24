//
// Created by Good_Pudge.
//

#include <ohf/ssl/SSL.hpp>
#include <ohf/Exception.hpp>
#include "Util.hpp"


namespace ohf {
    namespace ssl {
        SSL::SSL(const Context &context) : pImpl(new impl), context(context) {
            ssl_st* &ssl = pImpl->ssl;
            ssl = SSL_new(context.pImpl->context);
            if(!ssl) {
                throw Exception(Exception::Code::SSL_CREATE_ERROR,
                        "SSL create error: " + getOpenSSLError());
            }
        }

        SSL::~SSL() {
            if(pImpl->ssl) SSL_free(pImpl->ssl);
            delete pImpl;
        };

        void SSL::setHandle(Socket::Handle handle) {
            SSL_set_fd(pImpl->ssl, handle);
        }

        Socket::Handle SSL::getHandle() {
            return SSL_get_fd(pImpl->ssl);
        }

        void SSL::setTLSExtHostName(const std::string &hostname) {
            SSL_set_tlsext_host_name(pImpl->ssl, hostname.c_str());
        }

        void SSL::connect() {
            if(SSL_connect(pImpl->ssl) <= 0) {
                throw Exception(Exception::Code::SSL_CREATE_CONNECTION_ERROR,
                        "SSL create connection error: " + getOpenSSLError());
            }
        }

        Int32 SSL::write(const char *data, Int32 size) {
            if(!data || size == 0) throw Exception(Exception::Code::NO_DATA_TO_SEND, "No data to send: ");

            int length = SSL_write(pImpl->ssl, data, size);
            checkIO(length);

            return length;
        }

        Int32 SSL::read(char *data, Int32 size) {
            int length = SSL_read(pImpl->ssl, data, size);
            checkIO(length);
            return length;
        }

        void SSL::accept() {
            int error = SSL_accept(pImpl->ssl);
            checkIO(error);
        }

        void SSL::checkIO(Int32 length) {
            if(length < 0) {
                int error = SSL_get_error(pImpl->ssl, length);
                if(error != SSL_ERROR_WANT_READ && error != SSL_ERROR_WANT_WRITE) {
                    throw Exception(Exception::Code::SSL_ERROR,
                            "SSL error: " + getOpenSSLError());
                }
            }
        }
    }
}
