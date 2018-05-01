#include <catch.hpp>
#include "exception_matcher.hpp"
#include "time_unit_matcher.hpp"
#include <ohf/CacheControl.hpp>

using namespace ohf;

TEST_CASE("CacheControl") {
    CacheControl::Builder builder;
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

    CacheControl cacheControl = builder.build();
    REQUIRE(cacheControl.immutable());
    REQUIRE(cacheControl.noCache());
    REQUIRE(cacheControl.noStore());
    REQUIRE(cacheControl.noTransform());
    REQUIRE(cacheControl.onlyIfCached());
    REQUIRE_FALSE(cacheControl.mustRevalidate());
    REQUIRE_FALSE(cacheControl.isPublic());
    REQUIRE_FALSE(cacheControl.isPrivate());
    REQUIRE(cacheControl.sMaxAge() == TimeUnit::MINUS_ONE_SECOND);
    REQUIRE(cacheControl.maxAge() == 10.0_s);
    REQUIRE(cacheControl.maxStale() == 5.0_s);
    REQUIRE(cacheControl.minFresh() == 3.0_s);

    Headers headers = Headers::Builder()
            .add("Cache-Control", "public, private, no-cache, only-if-cached, must-revalidate, proxy-revalidate, "
                                  "immutable, no-store, no-transform, max-age=10, s-maxage=7, max-stale=5, "
                                  "min-fresh=3")
            .build();
    CacheControl cc(headers);
    TIMEUNIT_EQUAL(cc.sMaxAge(), 7.0_s);
    REQUIRE(cc.mustRevalidate());
    REQUIRE(cc.isPublic());
    REQUIRE(cc.isPrivate());

    CacheControl otherCC(headers);
    REQUIRE(cc == otherCC);

    headers = Headers::Builder()
            .set("Cache-Control", "max-age=INVALID")
            .build();
    REQUIRE_THROWS_CODE(CacheControl(headers), Exception::Code::INVALID_MAX_AGE);

    headers = Headers::Builder()
            .set("Cache-Control", "public, s-maxage=INVALID")
            .build();
    REQUIRE_THROWS_CODE(CacheControl(headers), Exception::Code::INVALID_S_MAX_AGE);

    headers = Headers::Builder()
            .set("Cache-Control", "max-stale=INVALID")
            .build();
    REQUIRE_THROWS_CODE(CacheControl(headers), Exception::Code::INVALID_MAX_STALE);

    headers = Headers::Builder()
            .set("Cache-Control", "min-fresh=INVALID")
            .build();
    REQUIRE_THROWS_CODE(CacheControl(headers), Exception::Code::INVALID_MIN_FRESH);

    CacheControl emptyCC;
    std::ostringstream oss;
    oss << emptyCC;
    REQUIRE(oss.str().empty());
}