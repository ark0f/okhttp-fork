//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSL_CIPHERSUITE_HPP
#define OKHTTPFORK_SSL_CIPHERSUITE_HPP

#include <string>
#include "ohf/Config.hpp"

namespace ohf {
    namespace ssl {
        class SSL;

        class CipherSuite {
        public:
            ~CipherSuite();

            Uint32 id() const;

            std::string name() const;

            std::string version() const;

        private:
            CipherSuite();

            struct impl;
            impl *pImpl;

            friend class SSL;
        };
    }
}

#endif //OKHTTPFORK_SSL_CIPHERSUITE_HPP
