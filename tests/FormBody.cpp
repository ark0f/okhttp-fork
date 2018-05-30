#include <catch.hpp>
#include "util/ExceptionCatch.hpp"
#include <ohf/FormBody.hpp>

using namespace ohf;

TEST_CASE("FormBody") {
    FormBody::Builder builder;
    SECTION("Builder") {
        builder
                .add("{q}", "Cat! and dogs?")
                .add("hello", "world");
    }

    FormBody formBody = builder.build();

    REQUIRE(formBody.name(0) == "{q}");
    REQUIRE_THROWS_CODE(formBody.name(2), ohf::Exception::Code::OUT_OF_RANGE);
    REQUIRE(formBody.encodedName(0) == "%7Bq%7D");

    REQUIRE(formBody.value(0) == "Cat! and dogs?");
    REQUIRE_THROWS_CODE(formBody.value(2), ohf::Exception::Code::OUT_OF_RANGE);
    REQUIRE(formBody.encodedValue(0) == "Cat%21%20and%20dogs%3F");

    REQUIRE(formBody.size() == 2);

    REQUIRE(formBody.contentType() == "application/x-www-form-urlencoded");
    REQUIRE(formBody.contentLength() == std::string("%7Bq%7D=Cat%21%20and%20dogs%3F&hello=world").size());
}