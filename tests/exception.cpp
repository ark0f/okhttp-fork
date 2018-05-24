#include <catch.hpp>
#include <exception_matcher.hpp>
#include <cstring>

using namespace ohf;

SCENARIO("Exception") {
    WHEN("Create simple exception") {
        Exception exception(Exception::Code::OK, "All right");
        GIVEN("Code: Exception::Code::OK and message: All right") {
            THEN("Getters should return these data too") {
                REQUIRE(exception.code() == Exception::Code::OK);
                REQUIRE(exception.message() == "All right");
                REQUIRE(strcmp(exception.what(), "All right") == 0);
            }
        }
    }

    WHEN("Get last exception") {
        const Exception *latest;
        GIVEN("Last exception") {
            latest = Exception::latest();
            THEN("Getters should return data of latest exception") {
                REQUIRE(latest->code() == Exception::Code::OK);
                REQUIRE(latest->message() == "All right");
                REQUIRE(strcmp(latest->what(), "All right") == 0);
            }
        }
    }
}