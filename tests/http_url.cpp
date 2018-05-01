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
                .setPathSegment(2, "oh/")
                .removePathSegment(1)
                .query("q=123&hello=world&empty_parameter")
                .setQueryParameter("unused", "parameter")
                .setQueryParameter("q", "321")
                .removeQueryParameter("unused")
                .fragment("some_fragment")
                .pathSuffix(false);

        REQUIRE_THROWS_CODE(builder.query("q=123=321"), Exception::Code::INVALID_QUERY_PARAMETER);
    }

    HttpURL url = builder.build();
    REQUIRE(url.scheme() == "ftp");
    REQUIRE(url.host() == "example.com");
    REQUIRE(url.port() == 1234);
    REQUIRE_FALSE(url.pathSuffix());
    REQUIRE(url.encodedPath() == "/wow/oh");
    REQUIRE(url.pathSegments()[0] == "wow");
    REQUIRE(url.pathSegments()[1] == "oh");
    REQUIRE(url.pathSize() == 7);
    REQUIRE(url.query() == "empty_parameter&hello=world&q=321");
    REQUIRE(url.queryParameter("q") == "321");
    REQUIRE(url.queryParameterName(0) == "empty_parameter");
    REQUIRE_THROWS_CODE(url.queryParameterName(3), Exception::Code::OUT_OF_RANGE);
    REQUIRE(url.queryParameterValue(0).empty());
    REQUIRE_THROWS_CODE(url.queryParameterValue(3), Exception::Code::OUT_OF_RANGE);
    REQUIRE(url.queryParameterNames()[0] == "empty_parameter");
    REQUIRE(url.querySize() == 33);
    REQUIRE(url.fragment() == "some_fragment");
    REQUIRE_FALSE(url.isHttps());
    REQUIRE(url.url() == "ftp://example.com/wow/oh?empty_parameter&hello=world&q=321#some_fragment");
}