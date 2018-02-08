#include <catch.hpp>
#include "exception_matcher.hpp"
#include <ohf/Request.hpp>

using namespace ohf;

TEST_CASE("Request") {
    Request::Builder builder;
    SECTION("Builder") {
        builder
                .url("https://example.com")
                .method("CREATE", RequestBody("application/json", "{}"))
                .headers(Headers::Builder()
                                .add("Set-Cookie", "key=value")
                                .add("Set-Cookie: hello=world")
                                .add("Host", "example.org")
                                .build())
                .cacheControl(CacheControl::Builder()
                                .immutable()
                                .maxAge(12.0_s)
                                .build())
                .removeHeader("Set-Cookie")
                .addHeader("Host", "example.com")
                .build();

        REQUIRE_THROWS_CODE(Request::Builder().build(), Exception::Code::METHOD_IS_NOT_NAMED);
        REQUIRE_THROWS_CODE(Request::Builder().delete_().build(), Exception::Code::URL_IS_NOT_NAMED);
    }

    Request request = builder.build();
    REQUIRE(request.header("host") == "example.org");
    REQUIRE(request.headers("host").size() == 2);
    REQUIRE(request.headers("host")[1] == "example.com");
    REQUIRE(request.url() == "https://example.com");
    REQUIRE(request.isHttps());
    REQUIRE(request.method() == "CREATE");
    REQUIRE(request.body().contentType() == "application/json");
    REQUIRE(request.body().contentLength() == 2);
    REQUIRE(request.cacheControl() == CacheControl::Builder()
            .immutable()
            .maxAge(12.0_s)
            .build());
}