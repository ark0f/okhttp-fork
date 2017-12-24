#include "catch.hpp"
#include <ohf/Headers.hpp>
#include <string>

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

        REQUIRE(builder.get("Set-Cookie") == "Hello=World");
        REQUIRE(builder.get("Host") == "unknown");


        builder.removeAll("Set-Cookie");
        REQUIRE(builder.get("Set-Cookie").empty());
    }

    ohf::Headers headers = builder.build();
    REQUIRE(headers.getDate().seconds() == 1445401728.0);
    REQUIRE(headers.get("Some") == "one");
    REQUIRE(headers.name(0) == "Some");
    REQUIRE(headers.value(0) == "one");
    REQUIRE(headers.pair(0) == ohf::Headers::ValueType("Some", "one"));
    REQUIRE(headers.size() == 4);

    ohf::Headers other = ohf::Headers::Builder()
            .add("Headers: not equal")
            .build();
    REQUIRE_FALSE(headers == other);


}
