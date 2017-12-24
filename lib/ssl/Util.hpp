//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSL_IMPLEMENTATIONS_HPP
#define OKHTTPFORK_SSL_IMPLEMENTATIONS_HPP

#include <ohf/ssl/SSL.hpp>
#include <ohf/ssl/Context.hpp>

#include <openssl/ssl.h>

namespace ohf {
    namespace ssl {
        struct SSL::impl {
            ::SSL *ssl;
        };

        struct Context::impl {
            ::SSL_CTX *context;
        };

        std::string getOpenSSLError();
    }
}

#endif //OKHTTPFORK_IMPLEMENTATIONS_HPP
