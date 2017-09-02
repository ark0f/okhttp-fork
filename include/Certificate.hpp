//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_CERTIFICATE_HPP
#define OKHTTPFORK_CERTIFICATE_HPP

namespace ohf {
    class Certificate {
    public:
        bool operator==(const Certificate &certificate);

        // abstract byte[] getEncoded();
        // abstract PublicKey getPublicKey();
        const char *getType();
        // abstract void verify(const PublicKey &publicKey);
        // abstract void verify(const PublicKey &publicKey, const char *sigProvider);
    protected:
        // object writeReplace();
    };
}

#endif //OKHTTPFORK_CERTIFICATE_HPP
