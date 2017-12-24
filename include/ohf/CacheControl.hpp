//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_CACHECONTROL_HPP
#define OKHTTPFORK_CACHECONTROL_HPP

#include "Config.hpp"
#include "Headers.hpp"

namespace ohf {
    class CacheControl {
    public:
        class Builder {
        public:
            Builder();

            CacheControl build();

            Builder &immutable();

            Builder &noCache();

            Builder &noStore();

            Builder &noTransform();

            Builder &onlyIfCached();

            Builder &maxAge(const TimeUnit &seconds);

            Builder &maxStale(const TimeUnit &seconds);

            Builder &minFresh(const TimeUnit &seconds);

        private:
            bool
                    mImmutable,
                    mNoCache,
                    mNoStore,
                    mNoTransform,
                    mOnlyIfCached;
            TimeUnit
                    mMaxAge,
                    mMaxStale,
                    mMinFresh;

            friend class ohf::CacheControl;
        };

        CacheControl();

        explicit CacheControl(Headers &headers);

        bool isPrivate() const;

        bool isPublic() const;

        bool immutable() const;

        bool mustRevalidate() const;

        bool noCache() const;

        bool noStore() const;

        bool noTransform() const;

        bool onlyIfCached() const;

        TimeUnit maxAge() const;

        TimeUnit maxStale() const;

        TimeUnit minFresh() const;

        TimeUnit sMaxAge() const;

        CacheControl *clone() const;

        std::string toString() const;

        bool operator==(const CacheControl &cc) const;

        friend std::ostream &operator<<(std::ostream &stream, const CacheControl &cacheControl);
    private:
        CacheControl(const Builder *builder);

        bool
                mPublic,
                mPrivate,
                mNoCache,
                mOnlyIfCached,
                mMustRevalidate,
                mImmutable,
                mNoStore,
                mNoTransform;
        TimeUnit
                mMaxAge,
                mSMaxAge,
                mMaxStale,
                mMinFresh;
    };
}

#endif //OKHTTPFORK_CACHECONTROL_HPP
