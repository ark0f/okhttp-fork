#include <catch.hpp>
#include "exception_matcher.hpp"
#include <ohf/HttpURL.hpp>

using namespace ohf;

TEST_CASE("HttpURL") {
    REQUIRE(HttpURL::defaultPort("http") == 80);
    REQUIRE(HttpURL::defaultPort("https") == 443);

    REQUIRE(HttpURL::decode("Hello%2C%20world%21") == "Hello, world!");
    REQUIRE_THROWS_CODE(HttpURL::decode("%ZZ"), Exception::Code::INVALID_URI_HEX_CODE);

    REQUIRE(HttpURL("example.com:214").url() == "http://example.com:214/");
    REQUIRE(HttpURL("example.com/#FrAgMeNt").url() == "http://example.com/#FrAgMeNt");
    REQUIRE(HttpURL("example.com/?q=123&land=en-US&empty").url() == "http://example.com/?empty&land=en-US&q=123");
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

    auto segments = url.encodedPathSegments();
    REQUIRE(segments[0] == "wow");
    REQUIRE(segments[1] == "oh");

    REQUIRE(url.query() == "empty_parameter&hello=world&q=321");
    REQUIRE(url.queryParameter("q") == "321");
    REQUIRE(url.queryParameterName(0) == "empty_parameter");

    auto query = url.queryMap();
    REQUIRE(query["empty_parameter"].empty());
    REQUIRE(query["hello"] == "world");
    REQUIRE(query["q"] == "321");

    REQUIRE_THROWS_CODE(url.queryParameterName(3), Exception::Code::OUT_OF_RANGE);
    REQUIRE(url.queryParameterValue(0).empty());
    REQUIRE_THROWS_CODE(url.queryParameterValue(3), Exception::Code::OUT_OF_RANGE);
    REQUIRE(url.queryParameterNames()[0] == "empty_parameter");
    REQUIRE(url.querySize() == 33);
    REQUIRE(url.fragment() == "some_fragment");
    REQUIRE_FALSE(url.isHttps());

    std::ostringstream oss;
    oss << url;
    REQUIRE(oss.str() == "ftp://example.com:1234/wow/oh?empty_parameter&hello=world&q=321#some_fragment");

    url = HttpURL::Builder()
            .host("example.com")
            .addPathSegments("path/")
            .build();
    REQUIRE(url.url() == "http://example.com/path/");
    REQUIRE(url.encodedQuery().empty());
}