#include <catch.hpp>
#include "exception_matcher.hpp"
#include <ohf/Headers.hpp>

TEST_CASE("Headers") {
    ohf::Headers::Builder builder;
    SECTION("Builder") {
        builder
                .add("Set-Cookie: Hello=World")
                .add("Set-Cookie: foo=bar")
                .add("Some", "one")
                .add("Host", "unknown")
                .add("Host", "example.com")
                .add("Date: Wed, 21 Oct 2015 07:28:00 GMT");

        REQUIRE_THROWS_CODE(builder.add(""), ohf::Exception::Code::HEADER_IS_EMPTY);

        REQUIRE(builder.get("Set-Cookie") == "Hello=World");
        REQUIRE(builder.get("Host") == "unknown");

        builder.removeAll("Set-Cookie");
        REQUIRE(builder.get("Set-Cookie").empty());
    }

    ohf::Headers headers = builder.build();
    // REQUIRE(headers.getDate().seconds() == 1445441280.0f); // ambiguous result on different platforms, compilators, build types
    REQUIRE(headers.get("Some") == "one");
    REQUIRE(headers.name(0) == "Some");
    REQUIRE_THROWS_CODE(headers.name(4), ohf::Exception::Code::OUT_OF_RANGE);
    REQUIRE(headers.value(0) == "one");
    REQUIRE_THROWS_CODE(headers.value(4), ohf::Exception::Code::OUT_OF_RANGE);
    REQUIRE(headers.pair(0) == ohf::Headers::Pair("Some", "one"));
    REQUIRE(headers.size() == 4);

    ohf::Headers other = ohf::Headers::Builder()
            .add("Headers: not equal")
            .build();
    REQUIRE_FALSE(headers == other);


    std::map<std::string, std::string> map;
    map["Set-Cookie"] = "COOKIE=";
    map["Host"] = "example.com";
    headers = ohf::Headers(map);

    REQUIRE(headers.name(0) == "Host");
    REQUIRE(headers.value(0) == "example.com");
    REQUIRE(headers.pair(1) == ohf::Headers::Pair("Set-Cookie", "COOKIE="));

    map.clear();
    map[""] = "";
    REQUIRE_THROWS_CODE(ohf::Headers(map), ohf::Exception::Code::HEADER_IS_EMPTY);
}
