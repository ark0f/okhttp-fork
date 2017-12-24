#include "catch.hpp"
#include <ohf/CacheControl.hpp>
#include <ohf/TimeUnit.hpp>

TEST_CASE("CacheControl") {
    ohf::CacheControl::Builder builder;
    SECTION("Builder") {
        builder
                .immutable()
                .noCache()
                .noStore()
                .noTransform()
                .onlyIfCached()
                .maxAge(ohf::TimeUnit::seconds(10))
                .maxStale(ohf::TimeUnit::seconds(5))
                .minFresh(ohf::TimeUnit::seconds(3));
    }

    ohf::CacheControl cacheControl = builder.build();
    REQUIRE(cacheControl.immutable());
    REQUIRE(cacheControl.noCache());
    REQUIRE(cacheControl.noStore());
    REQUIRE(cacheControl.noTransform());
    REQUIRE(cacheControl.onlyIfCached());
    REQUIRE_FALSE(cacheControl.mustRevalidate());
    REQUIRE_FALSE(cacheControl.isPublic());
    REQUIRE_FALSE(cacheControl.isPrivate());
    REQUIRE(cacheControl.sMaxAge() == ohf::TimeUnit::MINUS_ONE_SECOND);
    REQUIRE(cacheControl.maxAge() == ohf::TimeUnit::seconds(10));
    REQUIRE(cacheControl.maxStale() == ohf::TimeUnit::seconds(5));
    REQUIRE(cacheControl.minFresh() == ohf::TimeUnit::seconds(3));

    ohf::Headers headers = ohf::Headers::Builder()
            .add("Cache-Control", "public, private, no-cache, only-if-cached, must-revalidate, proxy-revalidate, "
                                  "immutable, no-store, no-transform, max-age=10, s-maxage=7, max-stale=5, "
                                  "min-fresh=3")
            .build();
    ohf::CacheControl cc(headers);
    REQUIRE(cc.sMaxAge() == ohf::TimeUnit::seconds(7));
    REQUIRE(cc.mustRevalidate());
    REQUIRE(cc.isPublic());
    REQUIRE(cc.isPrivate());

    ohf::CacheControl otherCC(headers);
    REQUIRE(cc == otherCC);
}