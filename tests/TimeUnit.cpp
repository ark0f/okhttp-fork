#include <catch.hpp>
#include <ohf/TimeUnit.hpp>
#include <util/TimeUnitCatch.hpp>

using namespace ohf;

SCENARIO("TimeUnit") {
    WHEN("Create TimeUnit::ZERO") {
        GIVEN("Count: 0, type: SECONDS") {
            THEN("It should be equals TimeUnit(0, TimeUnit::Type::SECONDS)") {
                REQUIRE_THAT(TimeUnit::ZERO, TimeUnitMatcher({0, TimeUnit::Type::SECONDS}));
            }
        }
    }

    WHEN("Create TimeUnit::MINUS_ONE_SECOND") {
        GIVEN("Count: -1, type: SECONDS") {
            THEN("It should be equals TimeUnit(-1, TimeUnit::Type::SECONDS)") {
                REQUIRE_THAT(TimeUnit::MINUS_ONE_SECOND, TimeUnitMatcher({-1, TimeUnit::Type::SECONDS}));
            }
        }
    }

    WHEN("Create using TimeUnit::seconds") {
        GIVEN("Count: 1.125, type: SECONDS") {
            THEN("It should be equals TimeUnit(1.125f)") {
                REQUIRE_THAT(TimeUnit::seconds(1.125f), TimeUnitMatcher(TimeUnit(1.125f)));
            }
        }
    }

    WHEN("Create using TimeUnit::milliseconds") {
        GIVEN("Count: 1125, type: MILLISECONDS") {
            THEN("It should be equals TimeUnit(1125, TimeUnit::Type::MILLISECONDS)") {
                REQUIRE_THAT(TimeUnit::milliseconds(1125), TimeUnitMatcher({1125, TimeUnit::Type::MILLISECONDS}));
            }
        }
    }

    WHEN("Create using TimeUnit::microseconds") {
        GIVEN("Count: 1125521, type: MICROSECONDS") {
            THEN("It should be equals TimeUnit(1125521, TimeUnit::Type::MICROSECONDS)") {
                REQUIRE_THAT(TimeUnit::microseconds(1125521), TimeUnitMatcher({1125521, TimeUnit::Type::MICROSECONDS}));
            }
        }
    }

    WHEN("Check literal operators") {
        GIVEN("Operator _s") {
            THEN("It should be equals TimeUnit(1.125f)") {
                REQUIRE_THAT(1.125_s, TimeUnitMatcher(TimeUnit(1.125f)));
            }
        }

        GIVEN("Operator _ms") {
            THEN("It should be equals TimeUnit(1125, TimeUnit::Type::MILLISECONDS)") {
                REQUIRE_THAT(1125_ms, TimeUnitMatcher({1125, TimeUnit::Type::MILLISECONDS}));
            }
        }

        GIVEN("Operator _us") {
            THEN("It should be equals TimeUnit(1125521, TimeUnit::Type::MICROSECONDS)") {
                REQUIRE_THAT(1125521_us, TimeUnitMatcher({1125521, TimeUnit::Type::MICROSECONDS}));
            }
        }
    }

    WHEN("Check bool operators") {
        GIVEN("TimeUnit i = 10.125_s") {
            THEN("Operator == should works correctly") {
                TimeUnit i = 10.125_s;
                REQUIRE(i == i);
                REQUIRE_FALSE(i == 521_ms);
            }

            THEN("Operator != should works correctly") {
                TimeUnit i = 10.125_s;
                REQUIRE(i != 10._s);
                REQUIRE_FALSE(i != i);
            }

            THEN("Operator >= should works correctly") {
                TimeUnit i = 10.125_s;
                REQUIRE(i >= i);
                REQUIRE(i >= 9._s);
                REQUIRE_FALSE(i >= 11._s);
            }

            THEN("Operator <= should works correctly") {
                TimeUnit i = 10.125_s;
                REQUIRE(i <= i);
                REQUIRE(i <= 11._s);
                REQUIRE_FALSE(i <= 9._s);
            }

            THEN("Operator > should works correctly") {
                TimeUnit i = 10.125_s;
                REQUIRE_FALSE(i > i);
                REQUIRE_FALSE(i > 11._s);
                REQUIRE(i > 9._s);
            }

            THEN("Operator < should works correctly") {
                TimeUnit i = 10.125_s;
                REQUIRE_FALSE(i < i);
                REQUIRE_FALSE(i < 9._s);
                REQUIRE(i < 11._s);
            }
        }
    }

    WHEN("Check math operators") {
        GIVEN("TimeUnit i = 10.125_s; TimeUnit j = 521_ms") {
            THEN("Operator + should works correctly") {
                TimeUnit i = 10.125_s;
                TimeUnit j = 521_ms;
                REQUIRE(i + j == 10.646_s);
            }

            THEN("Operator - should works correctly") {
                TimeUnit i = 10.125_s;
                TimeUnit j = 521_ms;
                REQUIRE(i - j == 9.604_s);
            }

            THEN("Operator * should works correctly") {
                TimeUnit i = 10.125_s;
                TimeUnit j = 521_ms;
                REQUIRE(i * j == 5275125000000_us);
            }

            THEN("Operator / should works correctly") {
                TimeUnit i = 10.125_s;
                TimeUnit j = 521_ms;
                REQUIRE(i / j == 0.000019_s);
            }

            THEN("Operator % should works correctly") {
                TimeUnit i = 10.125_s;
                TimeUnit j = 521_ms;
                REQUIRE(i % j == 226_ms);
            }

            THEN("Operator += should works correctly") {
                TimeUnit i = 10.125_s;
                TimeUnit j = 521_ms;
                i += j;
                REQUIRE(i == 10.646_s);
            }

            THEN("Operator -= should works correctly") {
                TimeUnit i = 10.125_s;
                TimeUnit j = 521_ms;
                i -= j;
                REQUIRE(i == 9.604_s);
            }

            THEN("Operator *= should works correctly") {
                TimeUnit i = 10.125_s;
                TimeUnit j = 521_ms;
                i *= j;
                REQUIRE(i == 5275125000000_us);
            }

            THEN("Operator /= should works correctly") {
                TimeUnit i = 10.125_s;
                TimeUnit j = 521_ms;
                i /= j;
                REQUIRE(i == 0.000019_s);
            }

            THEN("Operator %= should works correctly") {
                TimeUnit i = 10.125_s;
                TimeUnit j = 521_ms;
                i %= j;
                REQUIRE(i == 226_ms);
            }
        }
    }
}