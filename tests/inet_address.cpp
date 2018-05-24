#include <catch.hpp>
#include "exception_matcher.hpp"
#include <ohf/InetAddress.hpp>

#if WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif

using namespace ohf;

SCENARIO("InetAddress") {
    WHEN("Resolve several addresses") {
        GIVEN("Host: unknownhost and family: IP_UNKNOWN") {
            THEN("Should be exception") {
                REQUIRE_THROWS_CODE(InetAddress::getAllByName("unknownhost", IP_UNKNOWN), Exception::Code::UNKNOWN_HOST);
            }
        }

        GIVEN("Host: unknownhost and family: IPv4") {
            THEN("Should be exception") {
                REQUIRE_THROWS_CODE(InetAddress::getAllByName("unknownhost", IPv4), Exception::Code::UNKNOWN_HOST);
            }
        }

        GIVEN("Host: unknownhost and family: IPv6") {
            THEN("Should be exception") {
                REQUIRE_THROWS_CODE(InetAddress::getAllByName("unknownhost", IPv6), Exception::Code::UNKNOWN_HOST);
            }
        }
    }

    WHEN("Create InetAddress") {
        GIVEN("Host: localhost and family: IPv4") {
            InetAddress address("localhost", IPv4);
            THEN("Getters should return valid data") {
                REQUIRE(address.address() == std::array<Uint8, 16> {127, 0, 0, 1});
                REQUIRE(address.family() == IPv4);
                REQUIRE(address.hostAddress() == "127.0.0.1");
                REQUIRE(address.hostName() == "localhost");
                REQUIRE(address.originalType() == AF_INET);
            }
        }

        GIVEN("Host: localhost and family: IPv6") {
            InetAddress address("localhost", IPv6);
            THEN("Getters should return valid data") {
                REQUIRE(address.address() == std::array<Uint8, 16> {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1});
                REQUIRE(address.family() == IPv6);
                REQUIRE(address.hostAddress() == "::1");
                REQUIRE(address.hostName() == "localhost");
                REQUIRE(address.originalType() == AF_INET6);
            }
        }
    }
}