#include <catch.hpp>
#include <ohf/RangeException.hpp>
#include <cstring>

using namespace ohf;

SCENARIO("RangeException") {
    WHEN("Create simple exception") {
        GIVEN("Index: 534") {
            RangeException exception(534);
            THEN("Getters should return these data too") {
                REQUIRE(exception.code() == Exception::Code::OUT_OF_RANGE);
                REQUIRE(exception.message() == "Out of range: 534");
                REQUIRE(strcmp(exception.what(), "Out of range: 534") == 0);
                REQUIRE(exception.index() == 534);
            }
        }
    }
}