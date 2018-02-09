//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_TCP_SERVER_HPP
#define OKHTTPFORK_TCP_SERVER_HPP

#include <ohf/InetAddress.hpp>
#include <ohf/tcp/Socket.hpp>

namespace ohf {
    namespace tcp {
        friend class SSLServer;

        class Server : public ohf::Socket {
        public:
            class Connection {
            public:
                Connection(tcp::Socket *socket, const InetAddress &address, Uint16 port);

                ~Connection();

                tcp::Socket& socket() const;

                InetAddress address() const;

                Uint16 port() const;

                std::iostream& stream() const;
            private:
                tcp::Socket *mSocket;
                InetAddress mAddress;
                Uint16 mPort;
            };

            class Iterator {
            public:
                Iterator(const Server *server);

                Connection operator *() const;

                Connection operator ->() const;

                const Iterator& operator ++(Int32) const;

                const Iterator& operator ++() const;

                bool operator !=(const Iterator &right) const;

            private:
                const Server *server;
            };

            Server();

            Server(const InetAddress &address, Uint16 port);

            Server(const HttpURL &url);

            virtual void bind(const InetAddress &address, Uint16 port);

            void bind(const HttpURL &url);

            void listen(Int32 count) const;

            void listen() const;

            virtual Connection accept() const;

            const Iterator begin() const;

            Iterator begin();

            const Iterator end() const;

            Iterator end();
        };
    }
}

#endif //OKHTTPFORK_TCP_SERVER_HPP
