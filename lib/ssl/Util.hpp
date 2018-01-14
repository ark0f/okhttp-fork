//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSL_IMPLEMENTATIONS_HPP
#define OKHTTPFORK_SSL_IMPLEMENTATIONS_HPP

#include <ohf/ssl/SSL.hpp>
#include <ohf/ssl/Context.hpp>
#include <ohf/ssl/X509Certificate.hpp>
#include <ohf/ssl/CipherSuite.hpp>

#include <openssl/ssl.h>
#include <openssl/err.h>

namespace ohf {
    namespace ssl {
        struct SSL::impl {
            ::SSL *ssl;
        };

        struct Context::impl {
            SSL_CTX *context;
        };

        struct X509Certificate::impl {
            X509 *certificate;
        };

        struct CipherSuite::impl {
            const SSL_CIPHER *cipher;
        };

        inline std::string getOpenSSLError() {
            std::string error;
            unsigned long error_code;
            while ((error_code = ERR_get_error())) {
                char *str = ERR_error_string(error_code, nullptr);
                if (!str) return error;

                error += str;
            }
            return error;
        }
    }
}

#endif //OKHTTPFORK_IMPLEMENTATIONS_HPP
