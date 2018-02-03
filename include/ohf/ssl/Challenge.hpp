//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_CHALLENGE_HPP
#define OKHTTPFORK_CHALLENGE_HPP

#include "string"

namespace ohf {
    namespace ssl {
        class Challenge {
        public:
            Challenge(const std::string &scheme, const std::string &realm, const std::string &charset = "ISO-8859-1");

            std::string scheme() const;

            std::string realm() const;

            std::string charset() const;

            bool operator ==(const Challenge &right) const;

        private:
            std::string mScheme;
            std::string mRealm;
            std::string mCharset;
        };
    }
}

#endif //OKHTTPFORK_CHALLENGE_HPP
