//
// Created by Good_Pudge.
//

#include <ohf/ssl/SSL.hpp>
#include <ohf/ssl/Exception.hpp>
#include "Util.hpp"

namespace ohf {
    namespace ssl {
        SSL::SSL(const Context &context) : pImpl(new impl), context(context) {
            ssl_st* &ssl = pImpl->ssl;
            ssl = SSL_new(context.pImpl->context);
            if(!ssl) {
                throw Exception(Exception::Code::SSL_CREATE_ERROR);
            }
        }

        SSL::~SSL() {
            if(pImpl->ssl) SSL_free(pImpl->ssl);
            delete pImpl;
        };

        void SSL::setHandle(Socket::Handle handle) const {
            SSL_set_fd(pImpl->ssl, handle);
        }

        Socket::Handle SSL::getHandle() const {
            return (Socket::Handle) SSL_get_fd(pImpl->ssl);
        }

        void SSL::setTLSExtHostName(const std::string &hostname) const {
            SSL_set_tlsext_host_name(pImpl->ssl, hostname.c_str());
        }

        void SSL::connect() const {
            Int32 ret = SSL_connect(pImpl->ssl);
            if(ret <= 0) {
                throw Exception(Exception::Code::SSL_CREATE_CONNECTION_ERROR, *this, ret);
            }
        }

        Int32 SSL::write(const char *data, Int32 size) const {
            if(!data || size == 0) throw ohf::Exception(Exception::Code::NO_DATA_TO_SEND, "No data to send: ");

            int length = SSL_write(pImpl->ssl, data, size);
            checkIO(length);

            return length;
        }

        Int32 SSL::read(char *data, Int32 size) const {
            int length = SSL_read(pImpl->ssl, data, size);
            checkIO(length);
            return length;
        }

        void SSL::accept() const {
            int error = SSL_accept(pImpl->ssl);
            checkIO(error);
        }

        void SSL::checkIO(Int32 length) const {
            if(length < 0) {
                int error = SSL_get_error(pImpl->ssl, length);
                if(error != SSL_ERROR_WANT_READ && error != SSL_ERROR_WANT_WRITE) {
                    throw Exception(Exception::Code::SSL_ERROR, *this, length);
                }
            }
        }

        CipherSuite SSL::currentCipher() const {
            CipherSuite cipher;
            cipher.pImpl->cipher = SSL_get_current_cipher(pImpl->ssl);
            return cipher;
        }

        std::vector<CipherSuite> SSL::ciphers() const {
            std::vector<CipherSuite> ciphers;

            auto stack = SSL_get_ciphers(pImpl->ssl);
            for(int i = 0; i < sk_SSL_CIPHER_num(stack); i++) {
                auto ssl_cipher = sk_SSL_CIPHER_value(stack, i);

                CipherSuite cipher;
                cipher.pImpl->cipher = ssl_cipher;
                ciphers.push_back(cipher);
            }

            return ciphers;
        }
    }
}
