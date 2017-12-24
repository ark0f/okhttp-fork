#include "catch.hpp"
#include <ohf/HttpURL.hpp>

TEST_CASE("HttpURL") {
    ohf::HttpURL::Builder builder;
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
    }

    ohf::HttpURL url = builder.build();
    REQUIRE(url.scheme() == "ftp");
    REQUIRE(url.host() == "example.com");
    REQUIRE(url.port() == 1234);
    REQUIRE(url.encodedPath() == "/wow/bar/");
    REQUIRE(url.pathSegments()[0] == "wow");
    REQUIRE(url.pathSize() == 9);
    REQUIRE(url.query() == "hello=world&q=321");
    REQUIRE(url.queryParameter("q") == "321");
    REQUIRE(url.queryParameterName(0) == "hello");
    REQUIRE(url.queryParameterValue(0) == "world");
    REQUIRE(url.queryParameterNames()[0] == "hello");
    REQUIRE(url.querySize() == 17);
    REQUIRE(url.fragment() == "some_fragment");
    REQUIRE_FALSE(url.isHttps());
    REQUIRE(url.url() == "ftp://example.com/wow/bar/?hello=world&q=321#some_fragment");
}