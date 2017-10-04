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
            mMaxAge(-1),
            mMaxStale(-1),
            mMinFresh(-1) {}

    CacheControl &CacheControl::Builder::build() {
        CacheControl *cacheControl = (CacheControl *) std::malloc(sizeof(CacheControl));

        cacheControl->mImmutable = mImmutable;
        cacheControl->mNoCache = mNoCache;
        cacheControl->mNoStore = mNoStore;
        cacheControl->mNoTransform = mNoTransform;
        cacheControl->mOnlyIfCached = mOnlyIfCached;
        cacheControl->mMaxAge = mMaxAge;
        cacheControl->mMaxStale = mMaxStale;
        cacheControl->mMinFresh = mMinFresh;

        cacheControl->mPublic = false;
        cacheControl->mPrivate = false;
        cacheControl->mMustRevalidate = false;
        cacheControl->mSMaxAge = -1;

        return *cacheControl;
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

    CacheControl::Builder &CacheControl::Builder::maxAge(time_t seconds) {
        mMaxAge = seconds;
        return *this;
    }

    CacheControl::Builder &CacheControl::Builder::maxStale(time_t seconds) {
        mMaxStale = seconds;
        return *this;
    }

    CacheControl::Builder &CacheControl::Builder::minFresh(time_t seconds) {
        mMinFresh = seconds;
        return *this;
    }
}