#include <catch.hpp>
#include "exception_matcher.hpp"
#include <ohf/MultipartBody.hpp>

TEST_CASE("MultipartBody") {
    ohf::MultipartBody::Builder builder("BNDRY");
    SECTION("Builder") {
        builder
                .addFormDataPart("hello", "world")
                .addFormDataPart("photo", "image.png", ohf::RequestBody("image/png", "*content*"))
                .setType(ohf::MultipartBody::FORM);
    }

    ohf::MultipartBody body = builder.build();
    REQUIRE(body.size() == 2);
    REQUIRE(body.type() == "multipart/form-data");
    REQUIRE(body.contentType() == "multipart/form-data; boundary=BNDRY");
    REQUIRE(body.boundary() == "BNDRY");

    SECTION("Part") {
        auto part = body.part(0);
        REQUIRE(body.parts().size() == 2);
        
        REQUIRE(part.headers().get("Content-Disposition") == "form-data; name=\"hello\"");
        REQUIRE(part.body().contentLength() == 5);

        auto part2 = body.part(1);
        REQUIRE(part2.body().contentLength() == 9);
        REQUIRE(part2.headers().get("Content-Disposition")
                == "form-data; name=\"photo\"; filename=\"image.png\"");
        
    }
}