#include <catch.hpp>
#include <ohf/TimeUnit.hpp>
#include <util/TimeUnitCatch.hpp>

using namespace ohf;

SCENARIO("TimeUnit") {
    WHEN("Create TimeUnit::ZERO") {
        GIVEN("Count: 0, type: SECONDS") {
            REQUIRE_THAT(TimeUnit::ZERO, TimeUnitMatcher({0, TimeUnit::Type::SECONDS}));
        }
    }

    WHEN("Create TimeUnit::MINUS_ONE_SECOND") {
        GIVEN("Count: -1, type: SECONDS") {
            REQUIRE_THAT(TimeUnit::MINUS_ONE_SECOND, TimeUnitMatcher({-1, TimeUnit::Type::SECONDS}));
        }
    }

    WHEN("Create using TimeUnit::seconds") {
        GIVEN("Count: 1.125, type: SECONDS") {
            REQUIRE_THAT(TimeUnit::seconds(1.125f), TimeUnitMatcher(TimeUnit(1.125f)));
        }
    }

    WHEN("Create using TimeUnit::milliseconds") {
        GIVEN("Count: 1125, type: MILLISECONDS") {
            REQUIRE_THAT(TimeUnit::milliseconds(1125), TimeUnitMatcher({1125, TimeUnit::Type::MILLISECONDS}));
        }
    }

    WHEN("Create using TimeUnit::microseconds") {
        GIVEN("Count: 1125521, type: MICROSECONDS") {
            REQUIRE_THAT(TimeUnit::microseconds(1125521), TimeUnitMatcher({1125521, TimeUnit::Type::MICROSECONDS}));
        }
    }

    WHEN("Create using literal operator _s") {
        GIVEN("Count: 1.125, type: SECONDS") {
            REQUIRE_THAT(1.125_s, TimeUnitMatcher(TimeUnit(1.125f)));
        }
    }

    WHEN("Create using literal operator _ms") {
        GIVEN("Count: 1125, type: MILLISECONDS") {
            REQUIRE_THAT(1125_ms, TimeUnitMatcher({1125, TimeUnit::Type::MILLISECONDS}));
        }
    }

    WHEN("Create using literal operator _us") {
        GIVEN("Count: 1125521, type: MICROSECONDS") {
            REQUIRE_THAT(1125521_us, TimeUnitMatcher({1125521, TimeUnit::Type::MICROSECONDS}));
        }
    }

    // TODO: Operators check
}