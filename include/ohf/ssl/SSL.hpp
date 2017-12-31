//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSL_HPP
#define OKHTTPFORK_SSL_HPP

#include <ohf/Socket.hpp>
#include <vector>
#include "Context.hpp"

namespace ohf {
    namespace ssl {
        class Exception;

        class SSL {
        public:
            explicit SSL(const Context &context);

            ~SSL();

            void setHandle(Socket::Handle handle);

            Socket::Handle getHandle();

            void setTLSExtHostName(const std::string &hostname);

            void connect();
            
            Int32 write(const char *data, Int32 size);

            Int32 read(char *data, Int32 size);

            void accept();
        private:
            void checkIO(Int32 length);

            struct impl;
            impl *pImpl;

            const Context &context;

            friend class ohf::ssl::Exception;
        };
    }
}

#endif //OKHTTPFORK_SSL_HPP
