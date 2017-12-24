#include "catch.hpp"
#include <ohf/FormBody.hpp>

TEST_CASE("FormBody") {
    ohf::FormBody::Builder builder;
    SECTION("Builder") {
        builder
                .add("{q}", "Cat! and dogs?")
                .add("hello", "world");
    }

    ohf::FormBody formBody = builder.build();

    REQUIRE(formBody.name(0) == "{q}");
    REQUIRE(formBody.encodedName(0) == "%7Bq%7D");

    REQUIRE(formBody.value(0) == "Cat! and dogs?");
    REQUIRE(formBody.encodedValue(0) == "Cat%21%20and%20dogs%3F");

    REQUIRE(formBody.size() == 2);

    REQUIRE(formBody.contentType() == "application/x-www-form-urlencoded");
    REQUIRE(formBody.contentLength() == std::string("%7Bq%7D=Cat%21%20and%20dogs%3F&hello=world").size());
}