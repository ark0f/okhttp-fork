//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_CERTIFICATEPINNER_HPP
#define OKHTTPFORK_CERTIFICATEPINNER_HPP

namespace ohf {
    class CertificatePinner {
    public:

        bool operator ==(const CertificatePinner &pinner) const;
    };
}

#endif //OKHTTPFORK_CERTIFICATEPINNER_HPP
