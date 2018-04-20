//
// Created by Good_Pudge.
//

#include "Util.hpp"

namespace ohf {
    namespace ssl {
        CipherSuite::CipherSuite() : pImpl(new impl) {}

        CipherSuite::~CipherSuite() {}

        Uint32 CipherSuite::id() const {
            return SSL_CIPHER_get_id(pImpl->cipher);
        }

        std::string CipherSuite::name() const {
            return SSL_CIPHER_get_name(pImpl->cipher);
        }

        std::string CipherSuite::version() const {
            return SSL_CIPHER_get_version(pImpl->cipher);
        }
    }
}