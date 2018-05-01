#include <catch.hpp>
#include <exception_matcher.hpp>
#include <ohf/udp/Socket.hpp>
#include <thread>

using namespace ohf;

#define A_PORT 50001
#define B_PORT 50002
#define INVALID_FD Socket::Handle(-1)

void a_func(udp::Socket& a) {
    a.bind("localhost", A_PORT);

    InetAddress address;
    Uint16 port;
    std::string data;
    a.receive(address, port, data, 128);
    REQUIRE(data == "B_HELLO");
    REQUIRE(address.hostAddress() == "127.0.0.1");
    REQUIRE(port == B_PORT);

    a.send(address, port, "A_WORLD");

    std::vector<char> dataVector(3);
    a.receive(address, port, dataVector);
    REQUIRE(dataVector[0] == 1);
    REQUIRE(dataVector[1] == 127);
    REQUIRE(dataVector[2] == -128);
}

void b_func(udp::Socket& b) {
    b.bind("localhost", B_PORT);

    b.send("localhost", A_PORT, "B_HELLO");

    InetAddress address;
    Uint16 port;
    std::string data;
    b.receive(address, port, data, 128);
    REQUIRE(data == "A_WORLD");
    REQUIRE(address.hostAddress() == "127.0.0.1");
    REQUIRE(port == A_PORT);

    std::vector<char> toSend = {1, 127, -128};
    b.send("localhost", A_PORT, toSend);
}

TEST_CASE("udp::Socket") {
    udp::Socket a;
    udp::Socket b;

    // create and close
    a.create();
    REQUIRE(a.fd() != INVALID_FD);
    a.close();
    REQUIRE(a.fd() == INVALID_FD);

    a.create();
    REQUIRE(a.fd() != INVALID_FD);
    a.unbind();
    REQUIRE(a.fd() == INVALID_FD);

    // exceptions
    b.bind("localhost", B_PORT);
    REQUIRE_THROWS_CODE(a.bind("localhost", B_PORT), Exception::Code::FAILED_TO_BIND_SOCKET);
    b.close();
    REQUIRE_THROWS_CODE(a.send("localhost", 0, nullptr, 128), Exception::Code::NO_DATA_TO_SEND);
    REQUIRE_THROWS_CODE(a.send("localhost", 0, "some data", 0), Exception::Code::NO_DATA_TO_SEND);
    REQUIRE_THROWS_CODE(a.send("localhost", 0, "some_data", std::numeric_limits<Int32>::max()), Exception::Code::DATAGRAM_PACKET_IS_TOO_BIG);
    a.close();
    REQUIRE_THROWS_CODE(a.send("localhost", 0, "abcde", 5), Exception::Code::FAILED_TO_SEND_DATA);
    std::string data;
    InetAddress address;
    Uint16 port;
    REQUIRE_THROWS_CODE(a.receive(address, port, data, 128), Exception::Code::FAILED_TO_RECEIVE_DATA);
    a.close();
    b.close();

    // send / receive
    std::thread a_thread(a_func, std::ref(a));
    std::thread b_thread(b_func, std::ref(b));
    a_thread.join();
    b_thread.join();
    a.close();
    b.close();

    // swap
    a.create();
    b.create();

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