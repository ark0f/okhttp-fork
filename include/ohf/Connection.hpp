//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_CONNECTION_HPP
#define OKHTTPFORK_CONNECTION_HPP

#include <ohf/ssl/Handshake.hpp>
#include <ohf/tcp/Socket.hpp>
#include <ohf/Protocol.hpp>
#include <ohf/Route.hpp>

namespace ohf {
    class Connection {
    public:
        ssl::Handshake handshake();

        Protocol protocol();

        Route route();

        tcp::Socket socket();

    };
}

#endif //OKHTTPFORK_CONNECTION_HPP
