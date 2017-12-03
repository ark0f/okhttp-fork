//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_HANDSHAKE_HPP
#define OKHTTPFORK_HANDSHAKE_HPP

#include "CipherSuite.hpp"
#include "Certificate.hpp"
#include "Principal.hpp"
#include "TLSVersion.hpp"
#include <vector>

namespace ohf {
    class Handshake {
    public:
        CipherSuite cipherSuite();

        bool operator==(const Handshake &handshake);

        // static Handshake get(const SSLSession &session);
        static Handshake get(const TLSVersion &tlsVersion, const CipherSuite &cipherSuite,
                             const std::vector<Certificate> &peerCertificates,
                             const std::vector<Certificate> &localCertificates);

        std::vector<Certificate> localCertificates();

        Principal localPrincipal();

        std::vector<Certificate> peerCertificates();

        Principal peerPrincipal();

        TLSVersion tlsVersion();
    };
}

#endif //OKHTTPFORK_HANDSHAKE_HPP
