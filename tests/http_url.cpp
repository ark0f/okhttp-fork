#include <catch.hpp>
#include "exception_matcher.hpp"
#include <ohf/HttpURL.hpp>

using namespace ohf;

TEST_CASE("HttpURL") {
    REQUIRE_THROWS_CODE(HttpURL::decode("%ZZ"), Exception::Code::INVALID_URI_HEX_CODE);
    REQUIRE_THROWS_CODE(HttpURL("example.com?q=123"), Exception::Code::INVALID_URI);
    REQUIRE_THROWS_CODE(HttpURL("example.com#123"), Exception::Code::INVALID_URI);
    REQUIRE_THROWS_CODE(HttpURL("/?q=123"), Exception::Code::HOST_IS_EMPTY);
    REQUIRE_THROWS_CODE(HttpURL("example.com:INVALID"), Exception::Code::INVALID_PORT);
    REQUIRE_THROWS_CODE(HttpURL("example.com/?q=123=321"), Exception::Code::INVALID_QUERY_PARAMETER);

    HttpURL::Builder builder;
    SECTION("Builder") {
        builder
                .scheme("ftp")
                .host("example.com")
                .port(1234)
                .addPathSegments("/foo/bar")
                .setPathSegment(0, "wow")
                .query("q=123&hello=world")
                .setQueryParameter("q", "321")
                .fragment("some_fragment");

        REQUIRE_THROWS_CODE(builder.query("q=123=321"), Exception::Code::INVALID_QUERY_PARAMETER);
    }

    HttpURL url = builder.build();
    REQUIRE(url.scheme() == "ftp");
    REQUIRE(url.host() == "example.com");
    REQUIRE(url.port() == 1234);
    REQUIRE(url.encodedPath() == "/wow/bar/");
    REQUIRE(url.pathSegments()[0] == "wow");
    REQUIRE(url.pathSize() == 9);
    REQUIRE(url.query() == "hello=world&q=321");
    REQUIRE(url.queryParameter("q") == "321");
    REQUIRE(url.queryParameterName(0) == "hello");
    REQUIRE_THROWS_CODE(url.queryParameterName(2), Exception::Code::OUT_OF_RANGE);
    REQUIRE(url.queryParameterValue(0) == "world");
    REQUIRE_THROWS_CODE(url.queryParameterValue(2), Exception::Code::OUT_OF_RANGE);
    REQUIRE(url.queryParameterNames()[0] == "hello");
    REQUIRE(url.querySize() == 17);
    REQUIRE(url.fragment() == "some_fragment");
    REQUIRE_FALSE(url.isHttps());
    REQUIRE(url.url() == "ftp://example.com/wow/bar/?hello=world&q=321#some_fragment");
}