#include <catch.hpp>
#include <exception_matcher.hpp>
#include <ohf/udp/Socket.hpp>
#include <thread>

using namespace ohf;

#define A_PORT 50001
#define B_PORT 50002
#define INVALID_FD Socket::Handle(-1)

void a_func(Socket::Family family) {
    udp::Socket a;
    a.bind({"localhost", family}, A_PORT);

    InetAddress address;
    Uint16 port;
    std::string data;
    a.receive(address, port, data, 128);
    REQUIRE(data == "B_HELLO");
    REQUIRE(port == B_PORT);
    if(family == ohf::IPv4)
        REQUIRE(address.hostAddress() == "127.0.0.1");
    else
        REQUIRE(address.hostAddress() == "::1");

    a.send(address, port, "A_WORLD");

    std::vector<char> dataVector;
    a.receive(address, port, dataVector, 3);
    REQUIRE(dataVector[0] == 1);
    REQUIRE(dataVector[1] == 127);
    REQUIRE(dataVector[2] == -128);
}

void b_func(Socket::Family family) {
    udp::Socket b;
    b.bind({"localhost", family}, B_PORT);

    b.send({"localhost", family}, A_PORT, "B_HELLO");

    InetAddress address;
    Uint16 port;
    std::string data;
    b.receive(address, port, data, 128);
    REQUIRE(data == "A_WORLD");
    REQUIRE(port == A_PORT);
    if(family == ohf::IPv4)
        REQUIRE(address.hostAddress() == "127.0.0.1");
    else
        REQUIRE(address.hostAddress() == "::1");

    std::vector<char> toSend = {1, 127, -128};
    b.send({"localhost", family}, A_PORT, toSend);
}

TEST_CASE("udp::Socket", "[socket]") {
    udp::Socket a;
    udp::Socket b;

    // create and close
    a.create(ohf::IPv4);
    REQUIRE(a.fd() != INVALID_FD);
    a.close();
    REQUIRE(a.fd() == INVALID_FD);

    a.create(ohf::IPv4);
    REQUIRE(a.fd() != INVALID_FD);
    a.unbind();
    REQUIRE(a.fd() == INVALID_FD);

    // exceptions
    b.bind({"localhost", ohf::IPv4}, B_PORT);
    REQUIRE_THROWS_CODE(a.bind({"localhost", ohf::IPv4}, B_PORT), Exception::Code::FAILED_TO_BIND_SOCKET);
    b.close();
    REQUIRE_THROWS_CODE(a.send({"localhost", ohf::IPv4}, 0, nullptr, 128), Exception::Code::NO_DATA_TO_SEND);
    REQUIRE_THROWS_CODE(a.send({"localhost", ohf::IPv4}, 0, "some data", 0), Exception::Code::NO_DATA_TO_SEND);
    REQUIRE_THROWS_CODE(a.send({"localhost", ohf::IPv4}, 0, "some_data", std::numeric_limits<Int32>::max()), Exception::Code::DATAGRAM_PACKET_IS_TOO_BIG);
    a.close();
    REQUIRE_THROWS_CODE(a.send({"localhost", ohf::IPv4}, 0, "abcde", 5), Exception::Code::FAILED_TO_SEND_DATA);
    std::string data;
    InetAddress address;
    Uint16 port;
    REQUIRE_THROWS_CODE(a.receive(address, port, data, 128), Exception::Code::FAILED_TO_RECEIVE_DATA);
    a.close();
    b.close();

    // send / receive
    std::vector<Socket::Family> families = {ohf::IPv4, ohf::IPv6};
    for(const auto& family : families) {
        std::thread a_thread(a_func, family);
        std::thread b_thread(b_func, family);
        a_thread.join();
        b_thread.join();
        a.close();
        b.close();
    }

    // swap
    a.create(ohf::IPv4);
    b.create(ohf::IPv4);

    a.blocking(false);

    auto a_fd = a.fd();
    auto b_fd = b.fd();
    bool a_blocking = a.isBlocking();
    bool b_blocking = b.isBlocking();

    std::swap(a, b);
    REQUIRE(a.fd() == b_fd);
    REQUIRE(a.isBlocking() == b_blocking);
    REQUIRE(b.fd() == a_fd);
    REQUIRE(b.isBlocking() == a_blocking);

    // rvalue
    a_fd = a.fd();
    a_blocking = a.isBlocking();
    udp::Socket rvalue(std::move(a));
    REQUIRE(rvalue.fd() == a_fd);
    REQUIRE(rvalue.isBlocking() == a_blocking);
    REQUIRE_FALSE(a.isValid());
    REQUIRE(a.isBlocking());

    auto rvalue_fd = rvalue.fd();
    bool rvalue_blocking = rvalue.isBlocking();
    a = std::move(rvalue);
    REQUIRE(a.fd() == rvalue_fd);
    REQUIRE(a.isBlocking() == rvalue_blocking);
    REQUIRE_FALSE(rvalue.isValid());
    REQUIRE(rvalue.isBlocking());

}