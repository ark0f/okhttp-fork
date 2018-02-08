#include <catch.hpp>
#include "exception_matcher.hpp"
#include <ohf/MultipartBody.hpp>

using namespace ohf;

TEST_CASE("MultipartBody") {
    MultipartBody::Builder builder("BNDRY");
    //SECTION("Builder") {
        builder
                .addFormDataPart("hello", "world")
                .addFormDataPart("photo", "image.png", ohf::RequestBody("image/png", "*content*"))
                .setType(MultipartBody::FORM);
    //}

    MultipartBody body = builder.build();
    REQUIRE(body.size() == 2);
    REQUIRE(body.type() == "multipart/form-data");
    REQUIRE(body.contentType() == "multipart/form-data; boundary=BNDRY");
    REQUIRE(body.boundary() == "BNDRY");

    SECTION("Part") {
        REQUIRE_THROWS_CODE(body.part(2), Exception::Code::OUT_OF_RANGE);

        auto part = body.part(0);
        REQUIRE(body.parts().size() == 2);
        
        REQUIRE(part.headers().get("Content-Disposition") == "form-data; name=\"hello\"");
        REQUIRE(part.body().contentLength() == 5);

        auto part2 = body.part(1);
        REQUIRE(part2.body().contentLength() == 9);
        REQUIRE(part2.headers().get("Content-Disposition")
                == "form-data; name=\"photo\"; filename=\"image.png\"");

        RequestBody requestBody("text/html", "*content*");

        Headers headers = Headers::Builder()
                .set("Content-Type", "text/html")
                .build();
        REQUIRE_THROWS_CODE(MultipartBody::Part(headers, body), Exception::Code::UNEXPECTED_HEADER);

        headers = Headers::Builder()
                .set("Content-Length", "123")
                .build();
        REQUIRE_THROWS_CODE(MultipartBody::Part(headers, body), Exception::Code::UNEXPECTED_HEADER);
    }
}