//
// Created by Good_Pudge.
//

#include <ohf/ssl/Socket.hpp>
#include "../SocketImpl.hpp"

namespace ohf {
    namespace ssl {
        Socket::Socket(Type type, const Context &context) :
                ohf::Socket(type),
                context(context),
                SNICalled(false)
        {}

        void Socket::create(Handle fd) {
            if(fd != SocketImpl::invalidSocket()) {
                ohf::Socket::create(fd);

                ssl = new SSL(context);
                ssl->setHandle(mFD);
            }
        }

        void Socket::close() {
            if(mFD != SocketImpl::invalidSocket()) {
                delete ssl;
                ohf::Socket::close();
            }
        }

        void Socket::sni(bool b) {
            SNICalled = b;
        }

        void Socket::sni(const InetAddress &address) {
            sni(true);
            if(ssl) ssl->setTLSExtHostName(address.hostName());
        }
    }
}