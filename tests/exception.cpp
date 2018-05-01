#include <catch.hpp>
#include <exception_matcher.hpp>
#include <cstring>

using namespace ohf;

TEST_CASE("Exception") {
    Exception exception(Exception::Code::OK, "All right");
    REQUIRE(exception.code() == Exception::Code::OK);
    REQUIRE(exception.message() == "All right");
    REQUIRE(strcmp(exception.what(), "All right") == 0);
}