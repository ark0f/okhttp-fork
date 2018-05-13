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
    REQUIRE(headers.getDate().seconds() == 1445412480.f);
    REQUIRE(headers.get("Some") == "one");
    REQUIRE(headers["Date"] == "Wed, 21 Oct 2015 07:28:00 GMT");
    REQUIRE(headers.get("Header that don't exist").empty());
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
    map["Connection"] = "close";
    headers = Headers(map);

    REQUIRE(headers.name(0) == "Connection");
    REQUIRE(headers.value(0) == "close");
    REQUIRE(headers.pair(1) == Headers::Pair("Host", "example.com"));

    map.clear();
    map[""] = "";
    REQUIRE_THROWS_CODE(Headers(map), Exception::Code::HEADER_IS_EMPTY);

    const Headers const_headers = headers;

    const auto const_iterator = const_headers.begin();
    auto iterator = headers.begin();
    REQUIRE(const_iterator == iterator);
    REQUIRE_FALSE(const_iterator != iterator);

    const auto const_iterator_end = const_headers.end();
    auto iterator_end = headers.end();
    REQUIRE(iterator_end == const_iterator_end);
    REQUIRE_FALSE(iterator_end != const_iterator_end);

    REQUIRE(const_iterator != const_iterator_end);
    REQUIRE(iterator != iterator_end);

    const auto& const_pair_r = *const_iterator;
    auto& pair_r = *iterator;
    REQUIRE(const_pair_r == pair_r);

    const auto*const_pair_p = const_iterator.operator->();
    auto* pair_p = iterator.operator->();
    REQUIRE(*const_pair_p == *pair_p);

    struct Access { // access to private members
        mutable bool outOfRange;
        Headers::Pair type;
        Uint32 index;
        const Headers *headers;
    };

    auto access = (Access *) &iterator;

    REQUIRE(++iterator == Headers::Iterator(1, &headers));
    REQUIRE(access->index == 1);
    REQUIRE(--iterator == Headers::Iterator(0, &headers));
    REQUIRE(access->index == 0);

    REQUIRE(iterator++ == Headers::Iterator(1, &headers));
    REQUIRE(access->index == 0);
    REQUIRE((iterator + 1)-- == Headers::Iterator(0, &headers));
    REQUIRE(access->index == 0);

    REQUIRE((iterator + 1) == Headers::Iterator(1, &headers));
    REQUIRE(access->index == 0);

    iterator += 1;
    REQUIRE((iterator - 1) == Headers::Iterator(0, &headers));
    iterator -= 1;
    REQUIRE(access->index == 0);

    REQUIRE((iterator += 2) == Headers::Iterator(2, &headers));
    REQUIRE(access->index == 2);
    REQUIRE((iterator -= 2) == Headers::Iterator(0, &headers));
    REQUIRE(access->index == 0);

    iterator += 3; // >=
    REQUIRE(iterator.isOutOfRange());

    iterator -= 3; // ==
    REQUIRE_FALSE(iterator.isOutOfRange());

    iterator -= 3; // <=
    REQUIRE(iterator.isOutOfRange());
}
