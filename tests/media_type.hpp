#include "catch.hpp"
#include <ohf/MediaType.hpp>

TEST_CASE("MediaType") {
    ohf::MediaType type = "text/html; charset=utf-8; boundary=some_boundary";
    REQUIRE(type.type() == "text");
    REQUIRE(type.subtype() == "html");
    REQUIRE(type.charset() == "utf-8");
    REQUIRE(type.boundary() == "some_boundary");
    REQUIRE(type.toString() == "text/html; charset=utf-8; boundary=some_boundary");

    ohf::MediaType otherType = "text/xml";
    REQUIRE(otherType.charset("windows-1251") == "windows-1251");
    REQUIRE(otherType.boundary("--123--") == "--123--");

    REQUIRE_FALSE(type == otherType);
}
