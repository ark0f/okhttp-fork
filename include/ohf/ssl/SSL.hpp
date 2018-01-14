//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSL_HPP
#define OKHTTPFORK_SSL_HPP

#include <ohf/Socket.hpp>
#include <vector>
#include <ohf/ssl/Context.hpp>
#include <ohf/ssl/CipherSuite.hpp>

namespace ohf {
    namespace ssl {
        class Exception;

        class SSL {
        public:
            explicit SSL(const Context &context);

            ~SSL();

            void setHandle(Socket::Handle handle) const;

            Socket::Handle getHandle() const;

            void setTLSExtHostName(const std::string &hostname) const;

            void connect() const;
            
            Int32 write(const char *data, Int32 size) const;

            Int32 read(char *data, Int32 size) const;

            void accept() const;

            CipherSuite currentCipher() const;

            std::vector<CipherSuite> ciphers() const;

        private:
            void checkIO(Int32 length) const;

            struct impl;
            impl *pImpl;

            const Context &context;

            friend class ohf::ssl::Exception;
        };
    }
}

#endif //OKHTTPFORK_SSL_HPP
