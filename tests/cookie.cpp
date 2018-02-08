#include <catch.hpp>
#include "exception_matcher.hpp"
#include <ohf/Cookie.hpp>

using namespace ohf;

TEST_CASE("Cookie") {
    Cookie::Builder builder;
    SECTION("Builder") {
        builder
                .name("Hello")
                .value("World")
                .path("/")
                .httpOnly()
                .secure()
                .expiresAt(10.0_s)
                .hostOnlyDomain("www.example.com");
    }

    Cookie cookie = builder.build();
    REQUIRE(cookie.name() == "Hello");
    REQUIRE(cookie.value() == "World");
    REQUIRE(cookie.path() == "/");
    REQUIRE(cookie.httpOnly());
    REQUIRE(cookie.secure());
    REQUIRE(cookie.expiresAt() == 10.0_s);
    REQUIRE(cookie.hostOnly());
    REQUIRE(cookie.domain() == "www.example.com");
    REQUIRE_FALSE(cookie.persistent());

    HttpURL url = "https://www.example.com";
    REQUIRE(cookie.matches(url));

    Headers headers = Headers::Builder()
            .add("Set-Cookie", "foo=bar; max-age=100")
            .add("Set-Cookie: foo=bar; max-age=100")
            .build();
    std::vector<Cookie> cookies = Cookie::parseAll(url, headers);
    REQUIRE(cookies[0] == cookies[1]);
    REQUIRE(cookies[0].toString() == "foo=bar; Path=/; Max-Age=100");

    REQUIRE_THROWS_CODE(Cookie(url, ""), Exception::Code::INVALID_COOKIE_LINE);
    REQUIRE_THROWS_CODE(Cookie(url, "name value"), Exception::Code::INVALID_COOKIE_NAME_VALUE);
    REQUIRE_THROWS_CODE(Cookie(url, "name=; max-age=minus_one"), Exception::Code::INVALID_MAX_AGE);
}