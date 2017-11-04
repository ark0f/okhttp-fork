//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_CIPHERSUITE_HPP
#define OKHTTPFORK_CIPHERSUITE_HPP

#include <string>
#include "Config.hpp"

namespace ohf {
    /*class CipherSuite {
    public:
        CipherSuite(const std::string &name, Uint16 code);

        Uint64 code() const;

        std::string name() const;

        //  static const CipherSuite TLS_NULL_WITH_NULL_NULL;
        static const CipherSuite TLS_RSA_WITH_NULL_MD5;
        static const CipherSuite TLS_RSA_WITH_NULL_SHA;
        static const CipherSuite TLS_RSA_EXPORT_WITH_RC4_40_MD5;
        static const CipherSuite TLS_RSA_WITH_RC4_128_MD5;
        static const CipherSuite TLS_RSA_WITH_RC4_128_SHA;
        //  static const CipherSuite TLS_RSA_EXPORT_WITH_RC2_CBC_40_MD5;
        //  static const CipherSuite TLS_RSA_WITH_IDEA_CBC_SHA;
        static const CipherSuite TLS_RSA_EXPORT_WITH_DES40_CBC_SHA;
        static const CipherSuite TLS_RSA_WITH_DES_CBC_SHA;
        static const CipherSuite TLS_RSA_WITH_3DES_EDE_CBC_SHA;
        //  static const CipherSuite TLS_DH_DSS_EXPORT_WITH_DES40_CBC_SHA;
        //  static const CipherSuite TLS_DH_DSS_WITH_DES_CBC_SHA;
        //  static const CipherSuite TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA;
        //  static const CipherSuite TLS_DH_RSA_EXPORT_WITH_DES40_CBC_SHA;
        //  static const CipherSuite TLS_DH_RSA_WITH_DES_CBC_SHA;
        //  static const CipherSuite TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA;
        static const CipherSuite TLS_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA;
        static const CipherSuite TLS_DHE_DSS_WITH_DES_CBC_SHA;
        static const CipherSuite TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA;
        static const CipherSuite TLS_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA;
        static const CipherSuite TLS_DHE_RSA_WITH_DES_CBC_SHA;
        static const CipherSuite TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA;
        static const CipherSuite TLS_DH_anon_EXPORT_WITH_RC4_40_MD5;
        static const CipherSuite TLS_DH_anon_WITH_RC4_128_MD5;
        static const CipherSuite TLS_DH_anon_EXPORT_WITH_DES40_CBC_SHA;
        static const CipherSuite TLS_DH_anon_WITH_DES_CBC_SHA;
        static const CipherSuite TLS_DH_anon_WITH_3DES_EDE_CBC_SHA;
        static const CipherSuite TLS_KRB5_WITH_DES_CBC_SHA;
        static const CipherSuite TLS_KRB5_WITH_3DES_EDE_CBC_SHA;
        static const CipherSuite TLS_KRB5_WITH_RC4_128_SHA;
        //  static const CipherSuite TLS_KRB5_WITH_IDEA_CBC_SHA;
        static const CipherSuite TLS_KRB5_WITH_DES_CBC_MD5;
        static const CipherSuite TLS_KRB5_WITH_3DES_EDE_CBC_MD5;
        static const CipherSuite TLS_KRB5_WITH_RC4_128_MD5;
        //  static const CipherSuite TLS_KRB5_WITH_IDEA_CBC_MD5;
        static const CipherSuite TLS_KRB5_EXPORT_WITH_DES_CBC_40_SHA;
        //  static const CipherSuite TLS_KRB5_EXPORT_WITH_RC2_CBC_40_SHA;
        static const CipherSuite TLS_KRB5_EXPORT_WITH_RC4_40_SHA;
        static const CipherSuite TLS_KRB5_EXPORT_WITH_DES_CBC_40_MD5;
        //  static const CipherSuite TLS_KRB5_EXPORT_WITH_RC2_CBC_40_MD5;
        static const CipherSuite TLS_KRB5_EXPORT_WITH_RC4_40_MD5;
        //  static const CipherSuite TLS_PSK_WITH_NULL_SHA;
        //  static const CipherSuite TLS_DHE_PSK_WITH_NULL_SHA;
        //  static const CipherSuite TLS_RSA_PSK_WITH_NULL_SHA;
        static const CipherSuite TLS_RSA_WITH_AES_128_CBC_SHA;
        //  static const CipherSuite TLS_DH_DSS_WITH_AES_128_CBC_SHA;
        //  static const CipherSuite TLS_DH_RSA_WITH_AES_128_CBC_SHA;
        static const CipherSuite TLS_DHE_DSS_WITH_AES_128_CBC_SHA;
        static const CipherSuite TLS_DHE_RSA_WITH_AES_128_CBC_SHA;
        static const CipherSuite TLS_DH_anon_WITH_AES_128_CBC_SHA;
        static const CipherSuite TLS_RSA_WITH_AES_256_CBC_SHA;
        //  static const CipherSuite TLS_DH_DSS_WITH_AES_256_CBC_SHA;
        //  static const CipherSuite TLS_DH_RSA_WITH_AES_256_CBC_SHA;
        static const CipherSuite TLS_DHE_DSS_WITH_AES_256_CBC_SHA;
        static const CipherSuite TLS_DHE_RSA_WITH_AES_256_CBC_SHA;
        static const CipherSuite TLS_DH_anon_WITH_AES_256_CBC_SHA;
        static const CipherSuite TLS_RSA_WITH_NULL_SHA256;
        static const CipherSuite TLS_RSA_WITH_AES_128_CBC_SHA256;
        static const CipherSuite TLS_RSA_WITH_AES_256_CBC_SHA256;
        //  static const CipherSuite TLS_DH_DSS_WITH_AES_128_CBC_SHA256;
        //  static const CipherSuite TLS_DH_RSA_WITH_AES_128_CBC_SHA256;
        static const CipherSuite TLS_DHE_DSS_WITH_AES_128_CBC_SHA256;
        static const CipherSuite TLS_RSA_WITH_CAMELLIA_128_CBC_SHA;
        //  static const CipherSuite TLS_DH_DSS_WITH_CAMELLIA_128_CBC_SHA;
        //  static const CipherSuite TLS_DH_RSA_WITH_CAMELLIA_128_CBC_SHA;
        static const CipherSuite TLS_DHE_DSS_WITH_CAMELLIA_128_CBC_SHA;
        static const CipherSuite TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA;
        //  static const CipherSuite TLS_DH_anon_WITH_CAMELLIA_128_CBC_SHA;
        static const CipherSuite TLS_DHE_RSA_WITH_AES_128_CBC_SHA256;
        //  static const CipherSuite TLS_DH_DSS_WITH_AES_256_CBC_SHA256;
        //  static const CipherSuite TLS_DH_RSA_WITH_AES_256_CBC_SHA256;
        static const CipherSuite TLS_DHE_DSS_WITH_AES_256_CBC_SHA256;
        static const CipherSuite TLS_DHE_RSA_WITH_AES_256_CBC_SHA256;
        static const CipherSuite TLS_DH_anon_WITH_AES_128_CBC_SHA256;
        static const CipherSuite TLS_DH_anon_WITH_AES_256_CBC_SHA256;
        static const CipherSuite TLS_RSA_WITH_CAMELLIA_256_CBC_SHA;
        //  static const CipherSuite TLS_DH_DSS_WITH_CAMELLIA_256_CBC_SHA;
        //  static const CipherSuite TLS_DH_RSA_WITH_CAMELLIA_256_CBC_SHA;
        static const CipherSuite TLS_DHE_DSS_WITH_CAMELLIA_256_CBC_SHA;
        static const CipherSuite TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA;
        //  static const CipherSuite TLS_DH_anon_WITH_CAMELLIA_256_CBC_SHA;
        static const CipherSuite TLS_PSK_WITH_RC4_128_SHA;
        static const CipherSuite TLS_PSK_WITH_3DES_EDE_CBC_SHA;
        static const CipherSuite TLS_PSK_WITH_AES_128_CBC_SHA;
        static const CipherSuite TLS_PSK_WITH_AES_256_CBC_SHA;
        //  static const CipherSuite TLS_DHE_PSK_WITH_RC4_128_SHA;
        //  static const CipherSuite TLS_DHE_PSK_WITH_3DES_EDE_CBC_SHA;
        //  static const CipherSuite TLS_DHE_PSK_WITH_AES_128_CBC_SHA;
        //  static const CipherSuite TLS_DHE_PSK_WITH_AES_256_CBC_SHA;
        //  static const CipherSuite TLS_RSA_PSK_WITH_RC4_128_SHA;
        //  static const CipherSuite TLS_RSA_PSK_WITH_3DES_EDE_CBC_SHA;
        //  static const CipherSuite TLS_RSA_PSK_WITH_AES_128_CBC_SHA;
        //  static const CipherSuite TLS_RSA_PSK_WITH_AES_256_CBC_SHA;
        static const CipherSuite TLS_RSA_WITH_SEED_CBC_SHA;
        //  static const CipherSuite TLS_DH_DSS_WITH_SEED_CBC_SHA;
        //  static const CipherSuite TLS_DH_RSA_WITH_SEED_CBC_SHA;
        //  static const CipherSuite TLS_DHE_DSS_WITH_SEED_CBC_SHA;
        //  static const CipherSuite TLS_DHE_RSA_WITH_SEED_CBC_SHA;
        //  static const CipherSuite TLS_DH_anon_WITH_SEED_CBC_SHA;
        static const CipherSuite TLS_RSA_WITH_AES_128_GCM_SHA256;
        static const CipherSuite TLS_RSA_WITH_AES_256_GCM_SHA384;
        static const CipherSuite TLS_DHE_RSA_WITH_AES_128_GCM_SHA256;
        static const CipherSuite TLS_DHE_RSA_WITH_AES_256_GCM_SHA384;
        //  static const CipherSuite TLS_DH_RSA_WITH_AES_128_GCM_SHA256;
        //  static const CipherSuite TLS_DH_RSA_WITH_AES_256_GCM_SHA384;
        static const CipherSuite TLS_DHE_DSS_WITH_AES_128_GCM_SHA256;
        static const CipherSuite TLS_DHE_DSS_WITH_AES_256_GCM_SHA384;
        //  static const CipherSuite TLS_DH_DSS_WITH_AES_128_GCM_SHA256;
        //  static const CipherSuite TLS_DH_DSS_WITH_AES_256_GCM_SHA384;
        static const CipherSuite TLS_DH_anon_WITH_AES_128_GCM_SHA256;
        static const CipherSuite TLS_DH_anon_WITH_AES_256_GCM_SHA384;
        //  static const CipherSuite TLS_PSK_WITH_AES_128_GCM_SHA256;
        //  static const CipherSuite TLS_PSK_WITH_AES_256_GCM_SHA384;
        //  static const CipherSuite TLS_DHE_PSK_WITH_AES_128_GCM_SHA256;
        //  static const CipherSuite TLS_DHE_PSK_WITH_AES_256_GCM_SHA384;
        //  static const CipherSuite TLS_RSA_PSK_WITH_AES_128_GCM_SHA256;
        //  static const CipherSuite TLS_RSA_PSK_WITH_AES_256_GCM_SHA384;
        //  static const CipherSuite TLS_PSK_WITH_AES_128_CBC_SHA256;
        //  static const CipherSuite TLS_PSK_WITH_AES_256_CBC_SHA384;
        //  static const CipherSuite TLS_PSK_WITH_NULL_SHA256;
        //  static const CipherSuite TLS_PSK_WITH_NULL_SHA384;
        //  static const CipherSuite TLS_DHE_PSK_WITH_AES_128_CBC_SHA256;
        //  static const CipherSuite TLS_DHE_PSK_WITH_AES_256_CBC_SHA384;
        //  static const CipherSuite TLS_DHE_PSK_WITH_NULL_SHA256;
        //  static const CipherSuite TLS_DHE_PSK_WITH_NULL_SHA384;
        //  static const CipherSuite TLS_RSA_PSK_WITH_AES_128_CBC_SHA256;
        //  static const CipherSuite TLS_RSA_PSK_WITH_AES_256_CBC_SHA384;
        //  static const CipherSuite TLS_RSA_PSK_WITH_NULL_SHA256;
        //  static const CipherSuite TLS_RSA_PSK_WITH_NULL_SHA384;
        //  static const CipherSuite TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_DH_DSS_WITH_CAMELLIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_DH_RSA_WITH_CAMELLIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_DHE_DSS_WITH_CAMELLIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_DH_anon_WITH_CAMELLIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256;
        //  static const CipherSuite TLS_DH_DSS_WITH_CAMELLIA_256_CBC_SHA256;
        //  static const CipherSuite TLS_DH_RSA_WITH_CAMELLIA_256_CBC_SHA256;
        //  static const CipherSuite TLS_DHE_DSS_WITH_CAMELLIA_256_CBC_SHA256;
        //  static const CipherSuite TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256;
        //  static const CipherSuite TLS_DH_anon_WITH_CAMELLIA_256_CBC_SHA256;
        static const CipherSuite TLS_EMPTY_RENEGOTIATION_INFO_SCSV;
        static const CipherSuite TLS_FALLBACK_SCSV;
        static const CipherSuite TLS_ECDH_ECDSA_WITH_NULL_SHA;
        static const CipherSuite TLS_ECDH_ECDSA_WITH_RC4_128_SHA;
        static const CipherSuite TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA;
        static const CipherSuite TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA;
        static const CipherSuite TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA;
        static const CipherSuite TLS_ECDHE_ECDSA_WITH_NULL_SHA;
        static const CipherSuite TLS_ECDHE_ECDSA_WITH_RC4_128_SHA;
        static const CipherSuite TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA;
        static const CipherSuite TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA;
        static const CipherSuite TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA;
        static const CipherSuite TLS_ECDH_RSA_WITH_NULL_SHA;
        static const CipherSuite TLS_ECDH_RSA_WITH_RC4_128_SHA;
        static const CipherSuite TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA;
        static const CipherSuite TLS_ECDH_RSA_WITH_AES_128_CBC_SHA;
        static const CipherSuite TLS_ECDH_RSA_WITH_AES_256_CBC_SHA;
        static const CipherSuite TLS_ECDHE_RSA_WITH_NULL_SHA;
        static const CipherSuite TLS_ECDHE_RSA_WITH_RC4_128_SHA;
        static const CipherSuite TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA;
        static const CipherSuite TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA;
        static const CipherSuite TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA;
        static const CipherSuite TLS_ECDH_anon_WITH_NULL_SHA;
        static const CipherSuite TLS_ECDH_anon_WITH_RC4_128_SHA;
        static const CipherSuite TLS_ECDH_anon_WITH_3DES_EDE_CBC_SHA;
        static const CipherSuite TLS_ECDH_anon_WITH_AES_128_CBC_SHA;
        static const CipherSuite TLS_ECDH_anon_WITH_AES_256_CBC_SHA;
        //  static const CipherSuite TLS_SRP_SHA_WITH_3DES_EDE_CBC_SHA;
        //  static const CipherSuite TLS_SRP_SHA_RSA_WITH_3DES_EDE_CBC_SHA;
        //  static const CipherSuite TLS_SRP_SHA_DSS_WITH_3DES_EDE_CBC_SHA;
        //  static const CipherSuite TLS_SRP_SHA_WITH_AES_128_CBC_SHA;
        //  static const CipherSuite TLS_SRP_SHA_RSA_WITH_AES_128_CBC_SHA;
        //  static const CipherSuite TLS_SRP_SHA_DSS_WITH_AES_128_CBC_SHA;
        //  static const CipherSuite TLS_SRP_SHA_WITH_AES_256_CBC_SHA;
        //  static const CipherSuite TLS_SRP_SHA_RSA_WITH_AES_256_CBC_SHA;
        //  static const CipherSuite TLS_SRP_SHA_DSS_WITH_AES_256_CBC_SHA;
        static const CipherSuite TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256;
        static const CipherSuite TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384;
        static const CipherSuite TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256;
        static const CipherSuite TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384;
        static const CipherSuite TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256;
        static const CipherSuite TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384;
        static const CipherSuite TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256;
        static const CipherSuite TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384;
        static const CipherSuite TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256;
        static const CipherSuite TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384;
        static const CipherSuite TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256;
        static const CipherSuite TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384;
        static const CipherSuite TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256;
        static const CipherSuite TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384;
        static const CipherSuite TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256;
        static const CipherSuite TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384;
        //  static const CipherSuite TLS_ECDHE_PSK_WITH_RC4_128_SHA;
        //  static const CipherSuite TLS_ECDHE_PSK_WITH_3DES_EDE_CBC_SHA;
        static const CipherSuite TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA;
        static const CipherSuite TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA;
        //  static const CipherSuite TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA256;
        //  static const CipherSuite TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA384;
        //  static const CipherSuite TLS_ECDHE_PSK_WITH_NULL_SHA;
        //  static const CipherSuite TLS_ECDHE_PSK_WITH_NULL_SHA256;
        //  static const CipherSuite TLS_ECDHE_PSK_WITH_NULL_SHA384;
        //  static const CipherSuite TLS_RSA_WITH_ARIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_RSA_WITH_ARIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_DH_DSS_WITH_ARIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_DH_DSS_WITH_ARIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_DH_RSA_WITH_ARIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_DH_RSA_WITH_ARIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_DHE_DSS_WITH_ARIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_DHE_DSS_WITH_ARIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_DHE_RSA_WITH_ARIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_DHE_RSA_WITH_ARIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_DH_anon_WITH_ARIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_DH_anon_WITH_ARIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_ECDHE_ECDSA_WITH_ARIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_ECDHE_ECDSA_WITH_ARIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_ECDH_ECDSA_WITH_ARIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_ECDH_ECDSA_WITH_ARIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_ECDHE_RSA_WITH_ARIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_ECDHE_RSA_WITH_ARIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_ECDH_RSA_WITH_ARIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_ECDH_RSA_WITH_ARIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_RSA_WITH_ARIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_RSA_WITH_ARIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_DHE_RSA_WITH_ARIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_DHE_RSA_WITH_ARIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_DH_RSA_WITH_ARIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_DH_RSA_WITH_ARIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_DHE_DSS_WITH_ARIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_DHE_DSS_WITH_ARIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_DH_DSS_WITH_ARIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_DH_DSS_WITH_ARIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_DH_anon_WITH_ARIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_DH_anon_WITH_ARIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_ECDHE_ECDSA_WITH_ARIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_ECDHE_ECDSA_WITH_ARIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_ECDH_ECDSA_WITH_ARIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_ECDH_ECDSA_WITH_ARIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_ECDHE_RSA_WITH_ARIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_ECDHE_RSA_WITH_ARIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_ECDH_RSA_WITH_ARIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_ECDH_RSA_WITH_ARIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_PSK_WITH_ARIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_PSK_WITH_ARIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_DHE_PSK_WITH_ARIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_DHE_PSK_WITH_ARIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_RSA_PSK_WITH_ARIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_RSA_PSK_WITH_ARIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_PSK_WITH_ARIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_PSK_WITH_ARIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_DHE_PSK_WITH_ARIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_DHE_PSK_WITH_ARIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_RSA_PSK_WITH_ARIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_RSA_PSK_WITH_ARIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_ECDHE_PSK_WITH_ARIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_ECDHE_PSK_WITH_ARIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_ECDH_ECDSA_WITH_CAMELLIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_ECDH_ECDSA_WITH_CAMELLIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_ECDHE_RSA_WITH_CAMELLIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_ECDHE_RSA_WITH_CAMELLIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_ECDH_RSA_WITH_CAMELLIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_ECDH_RSA_WITH_CAMELLIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_RSA_WITH_CAMELLIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_RSA_WITH_CAMELLIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_DHE_RSA_WITH_CAMELLIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_DHE_RSA_WITH_CAMELLIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_DH_RSA_WITH_CAMELLIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_DH_RSA_WITH_CAMELLIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_DHE_DSS_WITH_CAMELLIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_DHE_DSS_WITH_CAMELLIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_DH_DSS_WITH_CAMELLIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_DH_DSS_WITH_CAMELLIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_DH_anon_WITH_CAMELLIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_DH_anon_WITH_CAMELLIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_ECDH_ECDSA_WITH_CAMELLIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_ECDH_ECDSA_WITH_CAMELLIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_ECDHE_RSA_WITH_CAMELLIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_ECDHE_RSA_WITH_CAMELLIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_ECDH_RSA_WITH_CAMELLIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_ECDH_RSA_WITH_CAMELLIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_PSK_WITH_CAMELLIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_PSK_WITH_CAMELLIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_DHE_PSK_WITH_CAMELLIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_DHE_PSK_WITH_CAMELLIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_RSA_PSK_WITH_CAMELLIA_128_GCM_SHA256;
        //  static const CipherSuite TLS_RSA_PSK_WITH_CAMELLIA_256_GCM_SHA384;
        //  static const CipherSuite TLS_PSK_WITH_CAMELLIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_PSK_WITH_CAMELLIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_DHE_PSK_WITH_CAMELLIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_DHE_PSK_WITH_CAMELLIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_RSA_PSK_WITH_CAMELLIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_RSA_PSK_WITH_CAMELLIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_ECDHE_PSK_WITH_CAMELLIA_128_CBC_SHA256;
        //  static const CipherSuite TLS_ECDHE_PSK_WITH_CAMELLIA_256_CBC_SHA384;
        //  static const CipherSuite TLS_RSA_WITH_AES_128_CCM;
        //  static const CipherSuite TLS_RSA_WITH_AES_256_CCM;
        //  static const CipherSuite TLS_DHE_RSA_WITH_AES_128_CCM;
        //  static const CipherSuite TLS_DHE_RSA_WITH_AES_256_CCM;
        //  static const CipherSuite TLS_RSA_WITH_AES_128_CCM_8;
        //  static const CipherSuite TLS_RSA_WITH_AES_256_CCM_8;
        //  static const CipherSuite TLS_DHE_RSA_WITH_AES_128_CCM_8;
        //  static const CipherSuite TLS_DHE_RSA_WITH_AES_256_CCM_8;
        //  static const CipherSuite TLS_PSK_WITH_AES_128_CCM;
        //  static const CipherSuite TLS_PSK_WITH_AES_256_CCM;
        //  static const CipherSuite TLS_DHE_PSK_WITH_AES_128_CCM;
        //  static const CipherSuite TLS_DHE_PSK_WITH_AES_256_CCM;
        //  static const CipherSuite TLS_PSK_WITH_AES_128_CCM_8;
        //  static const CipherSuite TLS_PSK_WITH_AES_256_CCM_8;
        //  static const CipherSuite TLS_PSK_DHE_WITH_AES_128_CCM_8;
        //  static const CipherSuite TLS_PSK_DHE_WITH_AES_256_CCM_8;
        //  static const CipherSuite TLS_ECDHE_ECDSA_WITH_AES_128_CCM;
        //  static const CipherSuite TLS_ECDHE_ECDSA_WITH_AES_256_CCM;
        //  static const CipherSuite TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8;
        //  static const CipherSuite TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8;
        static const CipherSuite TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256;
        static const CipherSuite TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256;
        //  static const CipherSuite TLS_DHE_RSA_WITH_CHACHA20_POLY1305_SHA256;
        //  static const CipherSuite TLS_PSK_WITH_CHACHA20_POLY1305_SHA256;
        //  static const CipherSuite TLS_ECDHE_PSK_WITH_CHACHA20_POLY1305_SHA256;
        //  static const CipherSuite TLS_DHE_PSK_WITH_CHACHA20_POLY1305_SHA256;
        //  static const CipherSuite TLS_RSA_PSK_WITH_CHACHA20_POLY1305_SHA256;
    private:
        std::string mName;
        Uint64 mCode;
    };*/

    class CipherSuite {
    public:
        enum {
            ECDHE_RSA_AES256_GCM_SHA384,
            ECDHE_ECDSA_AES256_GCM_SHA384,
            ECDHE_RSA_AES256_SHA384,
            ECDHE_ECDSA_AES256_SHA384,
            ECDHE_RSA_AES256_SHA,
            ECDHE_ECDSA_AES256_SHA,
            SRP_DSS_AES_256_CBC_SHA,
            SRP_RSA_AES_256_CBC_SHA,
            SRP_AES_256_CBC_SHA,
            DH_DSS_AES256_GCM_SHA384,
            DHE_DSS_AES256_GCM_SHA384,
            DH_RSA_AES256_GCM_SHA384,
            DHE_RSA_AES256_GCM_SHA384,
            DHE_RSA_AES256_SHA256,
            DHE_DSS_AES256_SHA256,
            DH_RSA_AES256_SHA256,
            DH_DSS_AES256_SHA256,
            DHE_RSA_AES256_SHA,
            DHE_DSS_AES256_SHA,
            DH_RSA_AES256_SHA,
            DH_DSS_AES256_SHA,
            DHE_RSA_CAMELLIA256_SHA,
            DHE_DSS_CAMELLIA256_SHA,
            DH_RSA_CAMELLIA256_SHA,
            DH_DSS_CAMELLIA256_SHA,
            ECDH_RSA_AES256_GCM_SHA384,
            ECDH_ECDSA_AES256_GCM_SHA384,
            ECDH_RSA_AES256_SHA384,
            ECDH_ECDSA_AES256_SHA384,
            ECDH_RSA_AES256_SHA,
            ECDH_ECDSA_AES256_SHA,
            AES256_GCM_SHA384,
            AES256_SHA256,
            AES256_SHA,
            CAMELLIA256_SHA,
            PSK_AES256_CBC_SHA,
            ECDHE_RSA_AES128_GCM_SHA256,
            ECDHE_ECDSA_AES128_GCM_SHA256,
            ECDHE_RSA_AES128_SHA256,
            ECDHE_ECDSA_AES128_SHA256,
            ECDHE_RSA_AES128_SHA,
            ECDHE_ECDSA_AES128_SHA,
            SRP_DSS_AES_128_CBC_SHA,
            SRP_RSA_AES_128_CBC_SHA,
            SRP_AES_128_CBC_SHA,
            DH_DSS_AES128_GCM_SHA256,
            DHE_DSS_AES128_GCM_SHA256,
            DH_RSA_AES128_GCM_SHA256,
            DHE_RSA_AES128_GCM_SHA256,
            DHE_RSA_AES128_SHA256,
            DHE_DSS_AES128_SHA256,
            DH_RSA_AES128_SHA256,
            DH_DSS_AES128_SHA256,
            DHE_RSA_AES128_SHA,
            DHE_DSS_AES128_SHA,
            DH_RSA_AES128_SHA,
            DH_DSS_AES128_SHA,
            DHE_RSA_SEED_SHA,
            DHE_DSS_SEED_SHA,
            DH_RSA_SEED_SHA,
            DH_DSS_SEED_SHA,
            DHE_RSA_CAMELLIA128_SHA,
            DHE_DSS_CAMELLIA128_SHA,
            DH_RSA_CAMELLIA128_SHA,
            DH_DSS_CAMELLIA128_SHA,
            ECDH_RSA_AES128_GCM_SHA256,
            ECDH_ECDSA_AES128_GCM_SHA256,
            ECDH_RSA_AES128_SHA256,
            ECDH_ECDSA_AES128_SHA256,
            ECDH_RSA_AES128_SHA,
            ECDH_ECDSA_AES128_SHA,
            AES128_GCM_SHA256,
            AES128_SHA256,
            AES128_SHA,
            SEED_SHA,
            CAMELLIA128_SHA,
            IDEA_CBC_SHA,
            PSK_AES128_CBC_SHA,
            ECDHE_RSA_RC4_SHA,
            ECDHE_ECDSA_RC4_SHA,
            ECDH_RSA_RC4_SHA,
            ECDH_ECDSA_RC4_SHA,
            RC4_SHA,
            RC4_MD5,
            PSK_RC4_SHA,
            ECDHE_RSA_DES_CBC3_SHA,
            ECDHE_ECDSA_DES_CBC3_SHA,
            SRP_DSS_3DES_EDE_CBC_SHA,
            SRP_RSA_3DES_EDE_CBC_SHA,
            SRP_3DES_EDE_CBC_SHA,
            EDH_RSA_DES_CBC3_SHA,
            EDH_DSS_DES_CBC3_SHA,
            DH_RSA_DES_CBC3_SHA,
            DH_DSS_DES_CBC3_SHA,
            ECDH_RSA_DES_CBC3_SHA,
            ECDH_ECDSA_DES_CBC3_SHA,
            DES_CBC3_SHA,
            PSK_3DES_EDE_CBC_SHA
        };

        static const char * forOpenSSL(int i);
    };
}

#endif //OKHTTPFORK_CIPHERSUITE_HPP
