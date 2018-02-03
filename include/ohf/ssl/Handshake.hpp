//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSL_HANDSHAKE_HPP
#define OKHTTPFORK_SSL_HANDSHAKE_HPP

#include <ohf/ssl/CipherSuite.hpp>
#include <ohf/ssl/X509Certificate.hpp>
#include <ohf/Principal.hpp>
#include <ohf/TLSVersion.hpp>
#include <ohf/ssl/SSL.hpp>
#include <vector>

namespace ohf {
    namespace ssl {
        class Handshake {
        public:
            Handshake() = default;

            explicit Handshake(SSL &ssl);

            Handshake(const TLSVersion &tlsVersion,
                      const CipherSuite &cipherSuite,
                      const std::vector<X509Certificate> &peerCertificates,
                      const std::vector<X509Certificate> &localCertificates);

            CipherSuite cipherSuite();

            bool operator ==(const Handshake &handshake) const;

            // static Handshake get(const SSLSession &session);
            static Handshake get(const TLSVersion &tlsVersion, const CipherSuite &cipherSuite,
                                 const std::vector<X509Certificate> &peerCertificates,
                                 const std::vector<X509Certificate> &localCertificates);

            std::vector<X509Certificate> localCertificates();

            Principal localPrincipal();

            std::vector<X509Certificate> peerCertificates();

            Principal peerPrincipal();

            TLSVersion tlsVersion();

        private:
            TLSVersion mVersion;
            //CipherSuite mSuite;
        };
    }
}

#endif //OKHTTPFORK_HANDSHAKE_HPP
