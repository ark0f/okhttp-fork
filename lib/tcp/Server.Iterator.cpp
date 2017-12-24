//
// Created by Good_Pudge.
//

#include <ohf/tcp/Server.hpp>
#include "../SocketImpl.hpp"

namespace ohf {
    namespace tcp {
        Server::Iterator::Iterator(const Server *server) : server(server) {}

        Server::Connection Server::Iterator::operator*() const {
            return server->accept();
        }

        Server::Connection Server::Iterator::operator->() const {
            return server->accept();
        }

        const Server::Iterator& Server::Iterator::operator++(Int32) const {
            return *this;
        }

        const Server::Iterator& Server::Iterator::operator++() const {
            return *this;
        }

        bool Server::Iterator::operator!=(const Iterator &right) const {
            return server->fd() != SocketImpl::invalidSocket()
                   || right.server->fd() != SocketImpl::invalidSocket();
        }
    }
}