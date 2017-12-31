//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSL_CONTEXT_HPP
#define OKHTTPFORK_SSL_CONTEXT_HPP

#include <ohf/TLSVersion.hpp>
#include <ohf/DTLSVersion.hpp>
#include <string>

namespace ohf {
    namespace ssl {
        class SSL;

        class Context {
        public:
            enum class FileType {
                ASN1,
                PEM
            };

            explicit Context(TLSVersion version);

            explicit Context(DTLSVersion version);

            ~Context();

            void loadCertificate(const std::string &file, const std::string &key);

        private:
            struct impl;
            impl *pImpl;

            friend class ohf::ssl::SSL;
        };
    }
}

#endif //OKHTTPFORK_SSL_CONTEXT_HPP
