//
// Created by Good_Pudge.
//

#include <ohf/ssl/Initializer.hpp>
#include "Util.hpp"

namespace ohf {
    namespace ssl {
        Initializer::Initializer() {
            SSL_library_init();
            SSLeay_add_ssl_algorithms();
            SSL_load_error_strings();
        }

        Initializer::~Initializer() {
            EVP_cleanup();
        }
    }
}
