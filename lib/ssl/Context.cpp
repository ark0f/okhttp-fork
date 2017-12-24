//
// Created by Good_Pudge.
//

#include <ohf/ssl/Context.hpp>
#include <ohf/Exception.hpp>
#include "Util.hpp"


namespace ohf {
    namespace ssl {
        Context::Context(TLSVersion version) : pImpl(new impl) {
            const SSL_METHOD *method;
            switch (version) {
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

            SSL_CTX *&context = pImpl->context;
            context = SSL_CTX_new(method);
            if(!context) {
                throw Exception(Exception::Code::SSL_CREATE_CONTEXT_ERROR,
                        "SSL create context error: " + getOpenSSLError());
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
                throw Exception(Exception::Code::SSL_FAILED_TO_USE_CERTIFICATE_FILE,
                        "SSL failed to use certificate file: " + getOpenSSLError());
            }

            if(SSL_CTX_use_PrivateKey_file(pImpl->context, key.c_str(), keyTI) <= 0) {
                throw Exception(Exception::Code::SSL_FAILED_TO_USE_PRIVATE_KEY_FILE,
                        "SSL failed to use private key file: " + getOpenSSLError());
            }

            if(!SSL_CTX_check_private_key(pImpl->context)) {
                throw Exception(Exception::Code::SSL_FAILED_TO_VERIFY_PRIVATE_KEY,
                        "SSL failed to verify private key: " + getOpenSSLError());
            }
        }
    }
}
