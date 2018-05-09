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
            .add("Set-Cookie", "foo=bar; secure; httpOnly; path=/example; domain=exampledomain; expires=Sun, 16 Jul 2018 06:23:41 GMT")
            .add("Set-Cookie: foo=bar; secure; httpOnly; path=/example; domain=exampledomain; max-age=1531722240")
            .build();
    std::vector<Cookie> cookies = Cookie::parseAll(url, headers);
    REQUIRE(cookies[0] == cookies[1]);
    std::ostringstream oss;
    oss << cookies[0];
    REQUIRE(oss.str() == "foo=bar; Path=/example; Domain=exampledomain; Max-Age=1531722240; HttpOnly; Secure");

    REQUIRE_THROWS_CODE(Cookie(url, ""), Exception::Code::INVALID_COOKIE_LINE);
    REQUIRE_THROWS_CODE(Cookie(url, "name value"), Exception::Code::INVALID_COOKIE_NAME_VALUE);
    REQUIRE_THROWS_CODE(Cookie(url, "name=; max-age=minus_one"), Exception::Code::INVALID_MAX_AGE);

    cookie = Cookie::Builder()
            .domain("exampledomain")
            .build();
    REQUIRE(cookie.domain() == "exampledomain");
}
