//
// Created by Good_Pudge.
//

#include <ohf/ssl/X509Certificate.hpp>
#include "Util.hpp"

namespace ohf {
    namespace ssl {
        X509Certificate::X509Certificate(Type type) : pImpl(new impl) {
            pImpl->certificate = X509_new();
        }

        X509Certificate::~X509Certificate() {
            X509_free(pImpl->certificate);
            delete pImpl;
        }
    }
}