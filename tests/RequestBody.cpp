#include <catch.hpp>
#include "util/ExceptionCatch.hpp"
#include <ohf/RequestBody.hpp>

TEST_CASE("RequestBody") {
    ohf::RequestBody body("text/html", "<html>Hello, world!</html>");
    REQUIRE(body.contentType() == "text/html");
    REQUIRE(body.contentLength() == 26);

    std::stringstream ss;
    ss << "Test reading from stream";
    ohf::RequestBody body2("text/plain", ss);
    REQUIRE(body2.contentLength() == 24);
}