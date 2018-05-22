#include <catch.hpp>
#include "../exception_matcher.hpp"
#include <ohf/tcp/Socket.hpp>
#include <ohf/tcp/Server.hpp>
#include <thread>

#define SERVER_PORT 50000

#define IPV4 Socket::Family::IPv4
#define IPV6 Socket::Family::IPv6

using namespace ohf;

void server_func(Socket::Family family) {
    tcp::Server server(family);
    server.bind({"localhost", family}, SERVER_PORT);
    server.listen();

    for(const auto& connection : server) {
        if(family == IPV4)
            REQUIRE(connection.address().hostAddress() == "127.0.0.1");
        else
            REQUIRE(connection.address().hostAddress() == "::1");

        std::iostream& ios = connection.stream();

        ios << "SERVER_DATA" << std::flush;

        std::string response;
        connection.socket().receive(response, 128);
        REQUIRE(response == "SOCKET_DATA");

        connection.close();
        break;
    }
}

void socket_func(Socket::Family family) {
    tcp::Socket socket(family);
    socket.connect({"localhost", family}, SERVER_PORT);
    std::iostream& ios = socket.stream();

    std::string response;
    socket.receive(response, 128);
    REQUIRE(response == "SERVER_DATA");

    ios << "SOCKET_DATA" << std::flush;

    socket.close();
}

TEST_CASE("tcp::Socket", "[socket]") {
    tcp::Socket socket(IPV4);
    tcp::Server server(IPV4);

    // exceptions
    REQUIRE_THROWS_CODE(socket.connect("localhost", 0), Exception::Code::FAILED_TO_CREATE_CONNECTION);
    REQUIRE_THROWS_CODE(socket.send(nullptr, 128), Exception::Code::NO_DATA_TO_SEND);
    REQUIRE_THROWS_CODE(socket.send("some_data", 0), Exception::Code::NO_DATA_TO_SEND);
    REQUIRE_THROWS_CODE(socket.send("some_data", 9), Exception::Code::FAILED_TO_SEND_DATA);
    REQUIRE_THROWS_CODE(socket.receive(nullptr, 128), Exception::Code::FAILED_TO_RECEIVE_DATA);

    server.bind({"localhost", IPV4}, SERVER_PORT);
    REQUIRE_THROWS_CODE(server.bind({"localhost", IPV4}, SERVER_PORT), Exception::Code::FAILED_TO_BIND_SOCKET);
    server.close();
    REQUIRE_THROWS_CODE(server.listen(), Exception::Code::FAILED_TO_LISTEN_SOCKET);
    REQUIRE_THROWS_CODE(server.accept(), Exception::Code::FAILED_TO_ACCEPT_SOCKET);
    socket.close();
    server.close();

    // send / receive
    std::vector<Socket::Family> families = {IPV4, IPV6};
    for(const auto& family : families) {
        std::thread server_thread(server_func, family);
        std::thread socket_thread(socket_func, family);
        socket_thread.join();
        server_thread.join();
        socket.close();
        server.close();
    }

    // swap
    socket.create();
    server.create();

    tcp::Socket b(IPV4);
    b.create();
    b.blocking(false);

    auto socket_fd = socket.fd();
    auto b_fd = b.fd();
    bool socket_blocking = socket.isBlocking();
    bool b_blocking = b.isBlocking();

    std::swap(socket, b);
    REQUIRE(socket.fd() == b_fd);
    REQUIRE(socket.isBlocking() == b_blocking);
    REQUIRE(b.fd() == socket_fd);
    REQUIRE(b.isBlocking() == socket_blocking);

    // rvalue
    socket_fd = socket.fd();
    socket_blocking = socket.isBlocking();
    tcp::Socket rvalue(std::move(socket));
    REQUIRE(rvalue.fd() == socket_fd);
    REQUIRE(rvalue.isBlocking() == socket_blocking);
    REQUIRE_FALSE(socket.isValid());
    REQUIRE(socket.isBlocking());

    auto rvalue_fd = rvalue.fd();
    bool rvalue_blocking = rvalue.isBlocking();
    socket = std::move(rvalue);
    REQUIRE(socket.fd() == rvalue_fd);
    REQUIRE(socket.isBlocking() == rvalue_blocking);
    REQUIRE_FALSE(rvalue.isValid());
    REQUIRE(rvalue.isBlocking());
}