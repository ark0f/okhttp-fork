#include <catch.hpp>
#include "exception_matcher.hpp"
#include <ohf/MediaType.hpp>

using namespace ohf;

TEST_CASE("MediaType") {
    MediaType type = "text/html; charset=utf-8; boundary=some_boundary";
    REQUIRE(type.type() == "text");
    REQUIRE(type.subtype() == "html");
    REQUIRE(type.charset() == "utf-8");
    REQUIRE(type.boundary() == "some_boundary");
    REQUIRE(type.toString() == "text/html; charset=utf-8; boundary=some_boundary");

    MediaType otherType = "text/xml";
    REQUIRE(otherType.charset("windows-1251") == "windows-1251");
    REQUIRE(otherType.boundary("--123--") == "--123--");

    REQUIRE_FALSE(type == otherType);

    REQUIRE_THROWS_CODE(MediaType(""), Exception::Code::INVALID_CONTENT_TYPE_LINE);
    REQUIRE_THROWS_CODE(MediaType("INVALID"), Exception::Code::INVALID_MIME_TYPE);
}
