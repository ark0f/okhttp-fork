//
// Created by Good_Pudge.
//

#include <openssl/err.h>
#include <ohf/Exception.hpp>
#include "Util.hpp"

namespace ohf {
    namespace ssl {
        std::string getOpenSSLError() {
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