//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_TCP_SERVER_HPP
#define OKHTTPFORK_TCP_SERVER_HPP

#include <ohf/InetAddress.hpp>
#include <ohf/tcp/Socket.hpp>

namespace ohf {
    namespace tcp {
        class Server;
    }
}

namespace std {
    void swap(ohf::tcp::Server& a, ohf::tcp::Server& b);
}

namespace ohf {
    namespace tcp {
        class Server : public virtual ohf::Socket {
        public:
            class Connection {
            public:
                Connection(tcp::Socket *socket, const InetAddress &address, Uint16 port);

                ~Connection();

                tcp::Socket& socket() const;

                InetAddress address() const;

                Uint16 port() const;

                std::iostream& stream() const;

                void close() const;

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

            explicit Server(Family family);

            Server(Family family, const InetAddress &address, Uint16 port);

            Server(Family family, const HttpURL &url);

            Server(Server&& server) noexcept;

            virtual void bind(const InetAddress &address, Uint16 port);

            void bind(const HttpURL &url);

            void listen(Int32 count) const;

            void listen() const;

            virtual Connection accept() const;

            const Iterator begin() const;

            Iterator begin();

            const Iterator end() const;

            Iterator end();

            Server& operator =(Server&& right) noexcept;

        private:
            friend void ::std::swap(Server& a, Server& b);
        };
    }
}

#endif //OKHTTPFORK_TCP_SERVER_HPP
