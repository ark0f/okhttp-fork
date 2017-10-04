//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_CACHECONTROL_HPP
#define OKHTTPFORK_CACHECONTROL_HPP

#include "Headers.hpp"

namespace ohf {
    class CacheControl {
    public:
        class Builder {
        public:
            Builder();

            CacheControl &build();

            Builder &immutable();

            Builder &noCache();

            Builder &noStore();

            Builder &noTransform();

            Builder &onlyIfCached();

            Builder &maxAge(time_t seconds);

            Builder &maxStale(time_t seconds);

            Builder &minFresh(time_t seconds);

        private:
            bool mImmutable;
            bool mNoCache;
            bool mNoStore;
            bool mNoTransform;
            bool mOnlyIfCached;
            time_t mMaxAge;
            time_t mMaxStale;
            time_t mMinFresh;

        };

        CacheControl(Headers &headers);

        bool isPrivate() const;

        bool isPublic() const;

        bool immutable() const;

        bool mustRevalidate() const;

        bool noCache() const;

        bool noStore() const;

        bool noTransform() const;

        bool onlyIfCached() const;

        time_t maxAgeSeconds() const;

        time_t maxStaleSeconds() const;

        time_t minFreshSeconds() const;

        time_t sMaxAgeSeconds() const;

    private:
        bool mPublic;
        bool mPrivate;
        bool mNoCache;
        bool mOnlyIfCached;
        bool mMustRevalidate;
        bool mImmutable;
        bool mNoStore;
        bool mNoTransform;
        time_t mMaxAge;
        time_t mSMaxAge;
        time_t mMaxStale;
        time_t mMinFresh;
        //bool
    };
}

#endif //OKHTTPFORK_CACHECONTROL_HPP
