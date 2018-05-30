#include <catch.hpp>
#include "util/ExceptionCatch.hpp"
#include <ohf/tcp/Socket.hpp>
#include <ohf/tcp/Server.hpp>
#include <thread>

#define SERVER_PORT 50000

using namespace ohf;

void server_func(Socket::Family family) {
    tcp::Server server;
    server.bind({"localhost", family}, SERVER_PORT);
    server.listen();

    for(const auto& connection : server) {
        if(family == ohf::IPv4)
            REQUIRE(connection.address().hostAddress() == "127.0.0.1");
        else
            REQUIRE(connection.address().hostAddress() == "::1");

        tcp::Socket::Stream stream(connection.socket());

        stream << "SERVER_DATA" << std::flush;

        std::string response(11, 0);
        stream.read(&response[0], 11);
        REQUIRE(response == "SOCKET_DATA");

        connection.close();
        break;
    }
}

void socket_func(Socket::Family family) {
    tcp::Socket socket;
    socket.connect({"localhost", family}, SERVER_PORT);
    tcp::Socket::Stream stream(socket);

    std::string response(11, 0);
    stream.read(&response[0], 11);
    REQUIRE(response == "SERVER_DATA");

    stream << "SOCKET_DATA" << std::flush;

    socket.close();
}

TEST_CASE("tcp::Socket", "[socket]") {
    tcp::Socket socket;
    tcp::Server server;

    // exceptions
    REQUIRE_THROWS_CODE(socket.connect("localhost", 0), Exception::Code::FAILED_TO_CREATE_CONNECTION);
    REQUIRE_THROWS_CODE(socket.send(nullptr, 128), Exception::Code::NO_DATA_TO_SEND);
    REQUIRE_THROWS_CODE(socket.send("some_data", 0), Exception::Code::NO_DATA_TO_SEND);
    REQUIRE_THROWS_CODE(socket.send("some_data", 9), Exception::Code::FAILED_TO_SEND_DATA);
    REQUIRE_THROWS_CODE(socket.receive(nullptr, 128), Exception::Code::FAILED_TO_RECEIVE_DATA);

    server.bind({"localhost", ohf::IPv4}, SERVER_PORT);
    REQUIRE_THROWS_CODE(server.bind({"localhost", ohf::IPv4}, SERVER_PORT), Exception::Code::FAILED_TO_BIND_SOCKET);
    server.close();
    REQUIRE_THROWS_CODE(server.listen(), Exception::Code::FAILED_TO_LISTEN_SOCKET);
    REQUIRE_THROWS_CODE(server.accept(), Exception::Code::FAILED_TO_ACCEPT_SOCKET);
    socket.close();
    server.close();

    // send / receive
    std::vector<Socket::Family> families = {ohf::IPv4, ohf::IPv4};
    for(const auto& family : families) {
        std::thread server_thread(server_func, family);
        std::thread socket_thread(socket_func, family);
        socket_thread.join();
        server_thread.join();
        socket.close();
        server.close();
    }

    // swap
    socket.create(ohf::IPv4);
    server.create(ohf::IPv4);

    tcp::Socket b;
    b.create(ohf::IPv4);
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