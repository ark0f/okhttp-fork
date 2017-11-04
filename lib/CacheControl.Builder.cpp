//
// Created by Good_Pudge.
//

#include "../include/CacheControl.hpp"

namespace ohf {
    CacheControl::Builder::Builder() :
            mImmutable(false),
            mNoCache(false),
            mNoStore(false),
            mNoTransform(false),
            mOnlyIfCached(false),
            mMaxAge(TimeUnit::MINUS_ONE_SECOND),
            mMaxStale(TimeUnit::MINUS_ONE_SECOND),
            mMinFresh(TimeUnit::MINUS_ONE_SECOND) {}

    CacheControl CacheControl::Builder::build() {
        return {this};
    }

    CacheControl::Builder &CacheControl::Builder::immutable() {
        mImmutable = true;
        return *this;
    }

    CacheControl::Builder &CacheControl::Builder::noCache() {
        mNoCache = true;
        return *this;
    }

    CacheControl::Builder &CacheControl::Builder::noStore() {
        mNoStore = true;
        return *this;
    }

    CacheControl::Builder &CacheControl::Builder::noTransform() {
        mNoTransform = true;
        return *this;
    }

    CacheControl::Builder &CacheControl::Builder::onlyIfCached() {
        mOnlyIfCached = true;
        return *this;
    }

    CacheControl::Builder &CacheControl::Builder::maxAge(const TimeUnit &seconds) {
        mMaxAge = seconds;
        return *this;
    }

    CacheControl::Builder &CacheControl::Builder::maxStale(const TimeUnit &seconds) {
        mMaxStale = seconds;
        return *this;
    }

    CacheControl::Builder &CacheControl::Builder::minFresh(const TimeUnit &seconds) {
        mMinFresh = seconds;
        return *this;
    }
}