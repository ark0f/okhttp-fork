#include <catch.hpp>
#include "exception_matcher.hpp"
#include "time_unit_matcher.hpp"
#include <ohf/CacheControl.hpp>

TEST_CASE("CacheControl") {
    using ohf::operator""_s;

    ohf::CacheControl::Builder builder;
    SECTION("Builder") {
        builder
                .immutable()
                .noCache()
                .noStore()
                .noTransform()
                .onlyIfCached()
                .maxAge(10.0_s)
                .maxStale(5.0_s)
                .minFresh(3.0_s);
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
    REQUIRE(cacheControl.maxAge() == 10.0_s);
    REQUIRE(cacheControl.maxStale() == 5.0_s);
    REQUIRE(cacheControl.minFresh() == 3.0_s);

    ohf::Headers headers = ohf::Headers::Builder()
            .add("Cache-Control", "public, private, no-cache, only-if-cached, must-revalidate, proxy-revalidate, "
                                  "immutable, no-store, no-transform, max-age=10, s-maxage=7, max-stale=5, "
                                  "min-fresh=3")
            .build();
    ohf::CacheControl cc(headers);
    TIMEUNIT_EQUAL(cc.sMaxAge(), 7.0_s);
    REQUIRE(cc.mustRevalidate());
    REQUIRE(cc.isPublic());
    REQUIRE(cc.isPrivate());

    ohf::CacheControl otherCC(headers);
    REQUIRE(cc == otherCC);

    headers = ohf::Headers::Builder()
            .add("Cache-Control: max-age=INVALID")
            .build();
    REQUIRE_THROWS_CODE(ohf::CacheControl(headers), ohf::Exception::Code::INVALID_MAX_AGE);
}