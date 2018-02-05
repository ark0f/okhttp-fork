//
// Created by Good_Pudge.
//

#include "Util.hpp"
#include <ohf/ssl/Exception.hpp>

namespace ohf {
    namespace ssl {
        std::string get_error(Exception::Code code) {
            std::string m_what;
            switch(code) {
                case Exception::Code::SSL_CREATE_ERROR:
                    m_what = "SSL create error: ";
                    break;
                case Exception::Code::SSL_CREATE_CONTEXT_ERROR:
                    m_what = "SSL create context error: ";
                    break;
                case Exception::Code::SSL_CREATE_CONNECTION_ERROR:
                    m_what = "SSL create connection error: ";
                    break;
                case Exception::Code::SSL_ERROR:
                    m_what = "SSL error: ";
                    break;
                case Exception::Code::SSL_ACCEPT_ERROR:
                    m_what = "SSL accept error: ";
                    break;
                case Exception::Code::SSL_FAILED_TO_USE_CERTIFICATE_FILE:
                    m_what = "SSL failed to use certificate file: ";
                    break;
                case Exception::Code::SSL_FAILED_TO_USE_PRIVATE_KEY_FILE:
                    m_what = "SSL failed to use private key file: ";
                    break;
                case Exception::Code::SSL_FAILED_TO_VERIFY_PRIVATE_KEY:
                    m_what = "SSL failed to verify private key: ";
                    break;
                case Exception::Code::SSL_PROTOCOL_DOES_NOT_SUPPORTED:
                    m_what = "SSL protocol doesn't supported: ";
                default: {
                    throw ohf::Exception(Exception::Code::INVALID_EXCEPTION_CODE,
                                         "Invalid exception code: " + std::to_string((Int32) code));
                }
            }
            return m_what;
        }

        Exception::Exception(const Code &code) :
                ohf::Exception(code, get_error(code)),
                ssl_code(0)
        {
            m_what += (ssl_message = getOpenSSLError());
        }

        Exception::Exception(const Exception::Code &code, const SSL &ssl, Int32 retCode) : Exception(code) {
            ssl_code = SSL_get_error(ssl.pImpl->ssl, retCode);
        }

        Int32 Exception::sslCode() const noexcept {
            return ssl_code;
        }

        std::string Exception::sslMessage() const noexcept {
            return ssl_message;
        }
    }
}

