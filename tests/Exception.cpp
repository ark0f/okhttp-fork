#include <catch.hpp>
#include <util/ExceptionCatch.hpp>
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
}