#include <catch.hpp>
#include "exception_matcher.hpp"
#include <ohf/Headers.hpp>

using namespace ohf;

TEST_CASE("Headers") {
    Headers::Builder builder;
    SECTION("Builder") {
        builder
                .add("Set-Cookie: Hello=World")
                .add("Set-Cookie: foo=bar")
                .add("Some", "one")
                .add("Host", "unknown")
                .add("Host", "example.com")
                .add("Date: Wed, 21 Oct 2015 07:28:00 GMT");

        REQUIRE_THROWS_CODE(builder.add(""), Exception::Code::HEADER_IS_EMPTY);

        REQUIRE(builder.get("Set-Cookie") == "Hello=World");
        REQUIRE(builder.get("Host") == "unknown");

        builder.removeAll("Set-Cookie");
        REQUIRE(builder.get("Set-Cookie").empty());
    }

    Headers headers = builder.build();
    // REQUIRE(headers.getDate().seconds() == 1445441280.0f); // ambiguous result on different platforms, compilators, build types
    REQUIRE(headers.get("Some") == "one");
    REQUIRE(headers.name(0) == "Some");
    REQUIRE_THROWS_CODE(headers.name(4), Exception::Code::OUT_OF_RANGE);
    REQUIRE(headers.value(0) == "one");
    REQUIRE_THROWS_CODE(headers.value(4), Exception::Code::OUT_OF_RANGE);
    REQUIRE(headers.pair(0) == Headers::Pair("Some", "one"));
    REQUIRE(headers.size() == 4);

    Headers other = Headers::Builder()
            .add("Headers: not equal")
            .build();
    REQUIRE_FALSE(headers == other);


    std::map<std::string, std::string> map;
    map["Set-Cookie"] = "COOKIE=";
    map["Host"] = "example.com";
    headers = Headers(map);

    REQUIRE(headers.name(0) == "Host");
    REQUIRE(headers.value(0) == "example.com");
    REQUIRE(headers.pair(1) == Headers::Pair("Set-Cookie", "COOKIE="));

    map.clear();
    map[""] = "";
    REQUIRE_THROWS_CODE(Headers(map), Exception::Code::HEADER_IS_EMPTY);
}
