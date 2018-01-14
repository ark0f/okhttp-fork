//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSL_X509CERTIFICATE_HPP
#define OKHTTPFORK_SSL_X509CERTIFICATE_HPP

#include <ohf/Config.hpp>
#include <vector>
#include <string>

namespace ohf {
    namespace ssl {
        class X509Certificate {
        public:
            enum class Type {
                PEM,
                ASN1
            };

            explicit X509Certificate(Type type);

            ~X509Certificate();

            bool operator ==(const X509Certificate &certificate);

            std::vector<Int8> getEncoded();
            // abstract PublicKey getPublicKey();
            Type type();
            // abstract void verify(const PublicKey &publicKey);
            // abstract void verify(const PublicKey &publicKey, const char *sigProvider);

        private:
            struct impl;
            impl *pImpl;
        };
    }
}

#endif //OKHTTPFORK_CERTIFICATE_HPP
