//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_TCP_SOCKET_HPP
#define OKHTTPFORK_TCP_SOCKET_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <ohf/Config.hpp>
#include <ohf/HttpURL.hpp>
#include <ohf/Socket.hpp>
#include <ohf/TimeUnit.hpp>
#include <ohf/InetAddress.hpp>
#include <ohf/IOStreamBuf.hpp>

namespace ohf {
    namespace tcp {
        class Socket : public ohf::Socket {
        public:
            class StreamBuf : public IOStreamBuf {
            public:
                StreamBuf(Int32 write, Int32 read);

                void socket(tcp::Socket *socket);

            private:
                tcp::Socket *mSocket;

            protected:
                Int32 write(const char *data, Int32 length) override;

                Int32 read(char *data, Int32 length) override;
            };

            explicit Socket(StreamBuf *buffer = new StreamBuf(1024, 1024));

            virtual void connect(const InetAddress &address, Uint16 port);

            void connect(const HttpURL &url);

            std::iostream &stream() const;

            void disconnect();

            virtual Int32 send(const char *data, Int32 size) const;

            Int32 send(const std::vector<Int8> &data) const;

            Int32 send(const std::string &data) const;

            virtual Int32 receive(char *data, Int32 size) const;

            std::vector<Int8> receive(Int32 size) const;

            std::string receiveString(Int32 size) const;

        private:
            std::shared_ptr<std::iostream> mIOS;
        };
    }
}

#endif //OKHTTPFORK_TCP_SOCKET_HPP
