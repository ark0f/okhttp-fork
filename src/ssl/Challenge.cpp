//
// Created by Good_Pudge.
//

#include <ohf/ssl/Challenge.hpp>

namespace ohf {
    namespace ssl {
        Challenge::Challenge(const std::string &scheme, const std::string &realm, const std::string &charset) :
                mScheme(scheme),
                mRealm(realm),
                mCharset(charset)
        {}

        std::string Challenge::scheme() const {
            return mScheme;
        }

        std::string Challenge::realm() const {
            return mRealm;
        }

        std::string Challenge::charset() const {
            return mCharset;
        }

        bool Challenge::operator ==(const Challenge &right) const {
            return mScheme == right.mScheme
                   && mRealm == right.mRealm
                   && mCharset == right.mCharset;
        }
    }
}