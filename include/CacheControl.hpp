//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_CACHECONTROL_HPP
#define OKHTTPFORK_CACHECONTROL_HPP

#include "Headers.hpp"

namespace ohf {
    class CacheControl {
    public:
        bool immutable();

        bool isPrivate();

        bool isPublic();

        int maxAgeSeconds();

        int maxStaleSeconds();

        int minFreshSeconds();

        bool mustRevalidate();

        bool noCache();

        bool noStore();

        bool noTransform();

        bool onlyIfCached();

        static CacheControl parse(Headers headers);

        int sMaxAgeSeconds();
    };
}

#endif //OKHTTPFORK_CACHECONTROL_HPP
