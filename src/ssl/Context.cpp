//
// Created by Good_Pudge.
//

#include <ohf/ssl/Context.hpp>
#include <ohf/ssl/Exception.hpp>
#include "Util.hpp"

namespace ohf {
    namespace ssl {
        Context::Context(TLSVersion version) : pImpl(new impl) {
            const SSL_METHOD *method;
            switch (version) {
                // OpenSSL 1.1.0
            #if OPENSSL_VERSION_NUMBER >= 0x10100000L
                case TLSVersion::TLS:
                    method = TLS_method();
            #endif

                // OpenSSL 1.0.2 and 1.1.0
                case TLSVersion::SSLv23:
                    method = SSLv23_method();
                    break;

                // OpenSSL 1.0.2
            #if OPENSSL_VERSION_NUMBER < 0x10100000L
                #ifndef OPENSSL_NO_SSL2
                case TLSVersion::SSLv2:
                    method = SSLv2_method();
                    break;
                #endif

                case TLSVersion::SSLv3:
                    method = SSLv3_method();
                    break;
            #endif

                // deprecated
            #ifndef OPENSSL_NO_TLS1_METHOD
                case TLSVersion::TLSv1:
                    method = TLSv1_method();
                    break;
            #endif

            #ifndef OPENSSL_NO_TLS1_1_METHOD
                case TLSVersion::TLSv1_1:
                    method = TLSv1_1_method();
                    break;
            #endif

            #ifndef OPENSSL_NO_TLS1_2_METHOD
                case TLSVersion::TLSv1_2:
                    method = TLSv1_2_method();
                    break;
            #endif

                default:
                    throw Exception(Exception::Code::SSL_PROTOCOL_DOES_NOT_SUPPORTED);
            }

            SSL_CTX *&context = pImpl->context;
            context = SSL_CTX_new(method);
            if(!context) {
                throw Exception(Exception::Code::SSL_CREATE_CONTEXT_ERROR);
            }
        }

        Context::Context(DTLSVersion version) : pImpl(new impl) {
            const SSL_METHOD *method;
            switch (version) {
        #ifdef OKHTTPFORK_DTLS
                case DTLSVersion::DTLS:
                    method = DTLS_method();
                    break;
            #ifndef OPENSSL_NO_DTLS1_METHOD
                case DTLSVersion::DTLSv1:
                    method = DTLSv1_method();
                    break;
            #endif

            #ifndef OPENSSL_NO_DTLS1_2_METHOD
                case DTLSVersion::DTLSv1_2:
                    method = DTLSv1_2_method();
                    break;
            #endif
        #endif
                default:
                    throw Exception(Exception::Code::SSL_PROTOCOL_DOES_NOT_SUPPORTED);

            }

            SSL_CTX* &context = pImpl->context;
            context = SSL_CTX_new(method);
            if(!context) {
                throw Exception(Exception::Code::SSL_CREATE_CONTEXT_ERROR);
            }
        }

        Context::~Context() {
            SSL_CTX_free(pImpl->context);
            delete pImpl;
        }

        void Context::loadCertificate(const std::string &file, const std::string &key) {
            /*Int32 fileTI;
            switch (fileType) {
                case FileType::ASN1:
                    fileTI = SSL_FILETYPE_ASN1;
                    break;
                case FileType::PEM:
                    fileTI = SSL_FILETYPE_PEM;
                    break;
            }

            Int32 keyTI;
            switch (keyType) {
                case FileType::ASN1:
                    keyTI = SSL_FILETYPE_ASN1;
                    break;
                case FileType::PEM:
                    keyTI = SSL_FILETYPE_PEM;
                    break;
            }*/

            Int32 fileTI = SSL_FILETYPE_PEM,
                  keyTI = SSL_FILETYPE_PEM;

            if(SSL_CTX_use_certificate_file(pImpl->context, file.c_str(), fileTI) <= 0) {
                throw Exception(Exception::Code::SSL_FAILED_TO_USE_CERTIFICATE_FILE);
            }

            if(SSL_CTX_use_PrivateKey_file(pImpl->context, key.c_str(), keyTI) <= 0) {
                throw Exception(Exception::Code::SSL_FAILED_TO_USE_PRIVATE_KEY_FILE);
            }

            if(!SSL_CTX_check_private_key(pImpl->context)) {
                throw Exception(Exception::Code::SSL_FAILED_TO_VERIFY_PRIVATE_KEY);
            }
        }
    }
}
