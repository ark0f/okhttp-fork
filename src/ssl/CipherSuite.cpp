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

        const char *CipherSuite::forOpenSSL(int i) {
            switch (i) {
                case ECDHE_RSA_AES256_GCM_SHA384:
                    return "ECDHE-RSA-AES256-GCM-SHA384";
                case ECDHE_ECDSA_AES256_GCM_SHA384:
                    return "ECDHE-ECDSA-AES256-GCM-SHA384";
                case ECDHE_RSA_AES256_SHA384:
                    return "ECDHE-RSA-AES256-SHA384";
                case ECDHE_ECDSA_AES256_SHA384:
                    return "ECDHE-ECDSA-AES256-SHA384";
                case ECDHE_RSA_AES256_SHA:
                    return "ECDHE-RSA-AES256-SHA";
                case ECDHE_ECDSA_AES256_SHA:
                    return "ECDHE-ECDSA-AES256-SHA";
                case SRP_DSS_AES_256_CBC_SHA:
                    return "SRP-DSS-AES-256-CBC-SHA";
                case SRP_RSA_AES_256_CBC_SHA:
                    return "SRP-RSA-AES-256-CBC-SHA";
                case SRP_AES_256_CBC_SHA:
                    return "SRP-AES-256-CBC-SHA";
                case DH_DSS_AES256_GCM_SHA384:
                    return "DH-DSS-AES256-GCM-SHA384";
                case DHE_DSS_AES256_GCM_SHA384:
                    return "DHE-DSS-AES256-GCM-SHA384";
                case DH_RSA_AES256_GCM_SHA384:
                    return "DH-RSA-AES256-GCM-SHA384";
                case DHE_RSA_AES256_GCM_SHA384:
                    return "DHE-RSA-AES256-GCM-SHA384";
                case DHE_RSA_AES256_SHA256:
                    return "DHE-RSA-AES256-SHA256";
                case DHE_DSS_AES256_SHA256:
                    return "DHE-DSS-AES256-SHA256";
                case DH_RSA_AES256_SHA256:
                    return "DH-RSA-AES256-SHA256";
                case DH_DSS_AES256_SHA256:
                    return "DH-DSS-AES256-SHA256";
                case DHE_RSA_AES256_SHA:
                    return "DHE-RSA-AES256-SHA";
                case DHE_DSS_AES256_SHA:
                    return "DHE-DSS-AES256-SHA";
                case DH_RSA_AES256_SHA:
                    return "DH-RSA-AES256-SHA";
                case DH_DSS_AES256_SHA:
                    return "DH-DSS-AES256-SHA";
                case DHE_RSA_CAMELLIA256_SHA:
                    return "DHE-RSA-CAMELLIA256-SHA";
                case DHE_DSS_CAMELLIA256_SHA:
                    return "DHE-DSS-CAMELLIA256-SHA";
                case DH_RSA_CAMELLIA256_SHA:
                    return "DH-RSA-CAMELLIA256-SHA";
                case DH_DSS_CAMELLIA256_SHA:
                    return "DH-DSS-CAMELLIA256-SHA";
                case ECDH_RSA_AES256_GCM_SHA384:
                    return "ECDH-RSA-AES256-GCM-SHA384";
                case ECDH_ECDSA_AES256_GCM_SHA384:
                    return "ECDH-ECDSA-AES256-GCM-SHA384";
                case ECDH_RSA_AES256_SHA384:
                    return "ECDH-RSA-AES256-SHA384";
                case ECDH_ECDSA_AES256_SHA384:
                    return "ECDH-ECDSA-AES256-SHA384";
                case ECDH_RSA_AES256_SHA:
                    return "ECDH-RSA-AES256-SHA";
                case ECDH_ECDSA_AES256_SHA:
                    return "ECDH-ECDSA-AES256-SHA";
                case AES256_GCM_SHA384:
                    return "AES256-GCM-SHA384";
                case AES256_SHA256:
                    return "AES256-SHA256";
                case AES256_SHA:
                    return "AES256-SHA";
                case CAMELLIA256_SHA:
                    return "CAMELLIA256-SHA";
                case PSK_AES256_CBC_SHA:
                    return "PSK-AES256-CBC-SHA";
                case ECDHE_RSA_AES128_GCM_SHA256:
                    return "ECDHE-RSA-AES128-GCM-SHA256";
                case ECDHE_ECDSA_AES128_GCM_SHA256:
                    return "ECDHE-ECDSA-AES128-GCM-SHA256";
                case ECDHE_RSA_AES128_SHA256:
                    return "ECDHE-RSA-AES128-SHA256";
                case ECDHE_ECDSA_AES128_SHA256:
                    return "ECDHE-ECDSA-AES128-SHA256";
                case ECDHE_RSA_AES128_SHA:
                    return "ECDHE-RSA-AES128-SHA";
                case ECDHE_ECDSA_AES128_SHA:
                    return "ECDHE-ECDSA-AES128-SHA";
                case SRP_DSS_AES_128_CBC_SHA:
                    return "SRP-DSS-AES-128-CBC-SHA";
                case SRP_RSA_AES_128_CBC_SHA:
                    return "SRP-RSA-AES-128-CBC-SHA";
                case SRP_AES_128_CBC_SHA:
                    return "SRP-AES-128-CBC-SHA";
                case DH_DSS_AES128_GCM_SHA256:
                    return "DH-DSS-AES128-GCM-SHA256";
                case DHE_DSS_AES128_GCM_SHA256:
                    return "DHE-DSS-AES128-GCM-SHA256";
                case DH_RSA_AES128_GCM_SHA256:
                    return "DH-RSA-AES128-GCM-SHA256";
                case DHE_RSA_AES128_GCM_SHA256:
                    return "DHE-RSA-AES128-GCM-SHA256";
                case DHE_RSA_AES128_SHA256:
                    return "DHE-RSA-AES128-SHA256";
                case DHE_DSS_AES128_SHA256:
                    return "DHE-DSS-AES128-SHA256";
                case DH_RSA_AES128_SHA256:
                    return "DH-RSA-AES128-SHA256";
                case DH_DSS_AES128_SHA256:
                    return "DH-DSS-AES128-SHA256";
                case DHE_RSA_AES128_SHA:
                    return "DHE-RSA-AES128-SHA";
                case DHE_DSS_AES128_SHA:
                    return "DHE-DSS-AES128-SHA";
                case DH_RSA_AES128_SHA:
                    return "DH-RSA-AES128-SHA";
                case DH_DSS_AES128_SHA:
                    return "DH-DSS-AES128-SHA";
                case DHE_RSA_SEED_SHA:
                    return "DHE-RSA-SEED-SHA";
                case DHE_DSS_SEED_SHA:
                    return "DHE-DSS-SEED-SHA";
                case DH_RSA_SEED_SHA:
                    return "DH-RSA-SEED-SHA";
                case DH_DSS_SEED_SHA:
                    return "DH-DSS-SEED-SHA";
                case DHE_RSA_CAMELLIA128_SHA:
                    return "DHE-RSA-CAMELLIA128-SHA";
                case DHE_DSS_CAMELLIA128_SHA:
                    return "DHE-DSS-CAMELLIA128-SHA";
                case DH_RSA_CAMELLIA128_SHA:
                    return "DH-RSA-CAMELLIA128-SHA";
                case DH_DSS_CAMELLIA128_SHA:
                    return "DH-DSS-CAMELLIA128-SHA";
                case ECDH_RSA_AES128_GCM_SHA256:
                    return "ECDH-RSA-AES128-GCM-SHA256";
                case ECDH_ECDSA_AES128_GCM_SHA256:
                    return "ECDH-ECDSA-AES128-GCM-SHA256";
                case ECDH_RSA_AES128_SHA256:
                    return "ECDH-RSA-AES128-SHA256";
                case ECDH_ECDSA_AES128_SHA256:
                    return "ECDH-ECDSA-AES128-SHA256";
                case ECDH_RSA_AES128_SHA:
                    return "ECDH-RSA-AES128-SHA";
                case ECDH_ECDSA_AES128_SHA:
                    return "ECDH-ECDSA-AES128-SHA";
                case AES128_GCM_SHA256:
                    return "AES128-GCM-SHA256";
                case AES128_SHA256:
                    return "AES128-SHA256";
                case AES128_SHA:
                    return "AES128-SHA";
                case SEED_SHA:
                    return "SEED-SHA";
                case CAMELLIA128_SHA:
                    return "CAMELLIA128-SHA";
                case IDEA_CBC_SHA:
                    return "IDEA-CBC-SHA";
                case PSK_AES128_CBC_SHA:
                    return "PSK-AES128-CBC-SHA";
                case ECDHE_RSA_RC4_SHA:
                    return "ECDHE-RSA-RC4-SHA";
                case ECDHE_ECDSA_RC4_SHA:
                    return "ECDHE-ECDSA-RC4-SHA";
                case ECDH_RSA_RC4_SHA:
                    return "ECDH-RSA-RC4-SHA";
                case ECDH_ECDSA_RC4_SHA:
                    return "ECDH-ECDSA-RC4-SHA";
                case RC4_SHA:
                    return "RC4-SHA";
                case RC4_MD5:
                    return "RC4-MD5";
                case PSK_RC4_SHA:
                    return "PSK-RC4-SHA";
                case ECDHE_RSA_DES_CBC3_SHA:
                    return "ECDHE-RSA-DES-CBC3-SHA";
                case ECDHE_ECDSA_DES_CBC3_SHA:
                    return "ECDHE-ECDSA-DES-CBC3-SHA";
                case SRP_DSS_3DES_EDE_CBC_SHA:
                    return "SRP-DSS-3DES-EDE-CBC-SHA";
                case SRP_RSA_3DES_EDE_CBC_SHA:
                    return "SRP-RSA-3DES-EDE-CBC-SHA";
                case SRP_3DES_EDE_CBC_SHA:
                    return "SRP-3DES-EDE-CBC-SHA";
                case EDH_RSA_DES_CBC3_SHA:
                    return "EDH-RSA-DES-CBC3-SHA";
                case EDH_DSS_DES_CBC3_SHA:
                    return "EDH-DSS-DES-CBC3-SHA";
                case DH_RSA_DES_CBC3_SHA:
                    return "DH-RSA-DES-CBC3-SHA";
                case DH_DSS_DES_CBC3_SHA:
                    return "DH-DSS-DES-CBC3-SHA";
                case ECDH_RSA_DES_CBC3_SHA:
                    return "ECDH-RSA-DES-CBC3-SHA";
                case ECDH_ECDSA_DES_CBC3_SHA:
                    return "ECDH-ECDSA-DES-CBC3-SHA";
                case DES_CBC3_SHA:
                    return "DES-CBC3-SHA";
                case PSK_3DES_EDE_CBC_SHA:
                    return "PSK-3DES-EDE-CBC-SHA";
                default:
                    return "UNKNOWN";
            }
        }
    }
}