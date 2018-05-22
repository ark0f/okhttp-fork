#include <catch.hpp>
#include "exception_matcher.hpp"
#include <ohf/InetAddress.hpp>

using namespace ohf;

TEST_CASE("InetAddress") {
    InetAddress address("localhost", Socket::Family::IPv4);
    REQUIRE(address.hostAddress() == "127.0.0.1");

    REQUIRE_THROWS_CODE(InetAddress("unknown_host.from_here"), Exception::Code::UNKNOWN_HOST);
}