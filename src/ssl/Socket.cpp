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
                SNICalled(true)
        {}

        void Socket::create(Handle fd) {
            if(fd != SocketImpl::invalidSocket()) {
                ohf::Socket::create(fd);

                mSSL = std::make_shared<SSL>(context);
                mSSL->setHandle(mFD);
            }
        }

        void Socket::close() {
            if(mFD != SocketImpl::invalidSocket()) {
                mSSL.reset();
                ohf::Socket::close();
            }
        }

        void Socket::sni(bool b) {
            SNICalled = b;
        }

        void Socket::sni(const InetAddress &address) {
            sni(true);
            if(mSSL) mSSL->setTLSExtHostName(address.hostName());
        }

        bool Socket::isSNI() const {
            return SNICalled;
        }

        const SSL& Socket::ssl() const {
            return *mSSL;
        }
    }
}