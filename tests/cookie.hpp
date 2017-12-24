#include "catch.hpp"
#include <ohf/Cookie.hpp>

TEST_CASE("Cookie") {
    ohf::Cookie::Builder builder;
    SECTION("Builder") {
        builder
                .name("Hello")
                .value("World")
                .path("/")
                .httpOnly()
                .secure()
                .expiresAt(ohf::TimeUnit::seconds(10))
                .hostOnlyDomain("www.example.com");
    }

    ohf::Cookie cookie = builder.build();
    REQUIRE(cookie.name() == "Hello");
    REQUIRE(cookie.value() == "World");
    REQUIRE(cookie.path() == "/");
    REQUIRE(cookie.httpOnly());
    REQUIRE(cookie.secure());
    REQUIRE(cookie.expiresAt() == ohf::TimeUnit::seconds(10));
    REQUIRE(cookie.hostOnly());
    REQUIRE(cookie.domain() == "www.example.com");
    REQUIRE_FALSE(cookie.persistent());

    ohf::HttpURL url = "https://www.example.com";
    REQUIRE(cookie.matches(url));

    ohf::Headers headers = ohf::Headers::Builder()
            .add("Set-Cookie", "foo=bar; max-age=100")
            .add("Set-Cookie: foo=bar; max-age=100")
            .build();
    std::vector<ohf::Cookie> cookies = ohf::Cookie::parseAll(url, headers);
    REQUIRE(cookies[0] == cookies[1]);
    REQUIRE(cookies[0].toString() == "foo=bar; Path=/; Max-Age=100");
}