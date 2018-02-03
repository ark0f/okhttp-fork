#include <catch.hpp>
#include "exception_matcher.hpp"
#include <ohf/Request.hpp>

TEST_CASE("Request") {
    ohf::Request::Builder builder;
    SECTION("Builder") {
        builder
                .url("https://example.com")
                .method("CREATE", ohf::RequestBody("application/json", "{}"))
                .headers(ohf::Headers::Builder()
                                .add("Set-Cookie", "key=value")
                                .add("Set-Cookie: hello=world")
                                .add("Host", "example.org")
                                .build())
                .cacheControl(ohf::CacheControl::Builder()
                                .immutable()
                                .maxAge(ohf::TimeUnit::seconds(12))
                                .build())
                .removeHeader("Set-Cookie")
                .addHeader("Host", "example.com")
                .build();
    }

    ohf::Request request = builder.build();
    REQUIRE(request.header("host") == "example.org");
    REQUIRE(request.headers("host").size() == 2);
    REQUIRE(request.headers("host")[1] == "example.com");
    REQUIRE(request.url() == "https://example.com");
    REQUIRE(request.isHttps());
    REQUIRE(request.method() == "CREATE");
    REQUIRE(request.body().contentType() == "application/json");
    REQUIRE(request.body().contentLength() == 2);
    REQUIRE(request.cacheControl() == ohf::CacheControl::Builder()
            .immutable()
            .maxAge(ohf::TimeUnit::seconds(10))
            .build());

}