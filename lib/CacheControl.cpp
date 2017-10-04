//
// Created by Good_Pudge.
//

#include "../include/CacheControl.hpp"
#include "../util/util.hpp"
#include "../util/string.hpp"
#include "../include/Exception.hpp"

using namespace util;
using namespace util::string;

namespace ohf {
    CacheControl::CacheControl(Headers &headers) :
            mPublic(false),
            mPrivate(false),
            mNoCache(false),
            mOnlyIfCached(false),
            mMustRevalidate(false),
            mImmutable(false),
            mNoStore(false),
            mNoTransform(false),
            mMaxAge(-1),
            mSMaxAge(-1),
            mMaxStale(-1),
            mMinFresh(-1) {
        std::vector<std::string> cache_control = split(std::move(headers.get("cache-control")), ", ");
        for (auto &element : cache_control) {
            util::string::toLower(element);
            std::vector<std::string> keyValue = split(element, "=");
            if (keyValue.size() == 1) {
                std::string key = keyValue[0];
                if (key == "public")
                    mPublic = true;
                else if (key == "private")
                    mPrivate = true;
                else if (key == "no-cache")
                    mNoCache = true;
                else if (key == "only-if-cached")
                    mOnlyIfCached = true;
                else if (key == "must-revalidate")
                    mMustRevalidate = true;
                else if (key == "proxy-revalidate" && mPublic)
                    mMustRevalidate = true;
                else if (key == "immutable")
                    mImmutable = true;
                else if (key == "no-store")
                    mNoStore = true;
                else if (key == "no-transform")
                    mNoTransform = true;
            } else if (keyValue.size() == 2) {
                std::string key = keyValue[0];
                std::string value = keyValue[1];
                if (key == "max-age")
                    try {
                        mMaxAge = std::stoi(value);
                    } catch (std::invalid_argument) {
                        throw Exception(Exception::Code::INVALID_MAX_AGE, "Invalid Max-Age: " + value);
                    }
                else if (key == "s-maxage" && mPublic)
                    try {
                        mSMaxAge = std::stoi(value);
                    } catch (std::invalid_argument) {
                        throw Exception(Exception::Code::INVALID_S_MAX_AGE, "Invalid S-MaxAge: " + value);
                    }
                else if (key == "max-stale")
                    try {
                        mMaxStale = std::stoi(value);
                    } catch (std::invalid_argument) {
                        throw Exception(Exception::Code::INVALID_MAX_STALE, "Invalid Max-Stale: " + value);
                    }
                else if (key == "min-fresh")
                    try {
                        mMinFresh = std::stoi(value);
                    } catch (std::invalid_argument) {
                        throw Exception(Exception::Code::INVALID_MIN_FRESH, "Invalid min fresh: " + value);
                    }
                // stale-while-revalidate=<seconds> ?
                // stale-if-error=<seconds> ?
            }
        }
    }

    bool CacheControl::isPublic() const {
        return mPublic;
    }

    bool CacheControl::isPrivate() const {
        return mPrivate;
    }

    bool CacheControl::immutable() const {
        return mImmutable;
    }

    bool CacheControl::mustRevalidate() const {
        return mMustRevalidate;
    }

    bool CacheControl::noCache() const {
        return mNoCache;
    }

    bool CacheControl::noStore() const {
        return mNoStore;
    }

    bool CacheControl::noTransform() const {
        return mNoTransform;
    }

    bool CacheControl::onlyIfCached() const {
        return mOnlyIfCached;
    }

    time_t CacheControl::maxAgeSeconds() const {
        return mMaxAge;
    }

    time_t CacheControl::maxStaleSeconds() const {
        return mMaxStale;
    }

    time_t CacheControl::minFreshSeconds() const {
        return mMinFresh;
    }

    time_t CacheControl::sMaxAgeSeconds() const {
        return mSMaxAge;
    }
}