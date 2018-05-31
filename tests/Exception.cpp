#include <catch.hpp>
#include <cstring>
#include <ohf/Exception.hpp>

using namespace ohf;

SCENARIO("Exception") {
    WHEN("Create simple exception") {
        GIVEN("Code: Exception::Code::OK and message: All right") {
            Exception exception(Exception::Code::OK, "All right");
            THEN("Getters should return these data too") {
                REQUIRE(exception.code() == Exception::Code::OK);
                REQUIRE(exception.message() == "All right");
                REQUIRE(strcmp(exception.what(), "All right") == 0);
            }
        }
    }
}