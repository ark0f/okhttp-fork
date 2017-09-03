//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_EXCEPTION_HPP
#define OKHTTPFORK_EXCEPTION_HPP

#include <string>
#include "../util/include/string.hpp"

namespace ohf {
    class Exception {
    public:
        enum Code {
            HEADER_NOT_EXISTS,
            INVALID_HEADER_LINE,
            INVALID_MIME_TYPE,
            FAILED_TO_READ_STREAM,
            FAILED_TO_CREATE_SOCKET,
            NO_SUCH_HOST,
            FAILED_TO_CREATE_CONNECTION,
            FAILED_TO_SEND_DATA,
            FAILED_TO_RECEIVE_DATA,
            FAILED_TO_DISCONNECT_SOCKET,
            FAILED_TO_CLEANUP_SOCKET,
            OPENSSL_INIT_ERROR,
            OPENSSL_CREATE_CONTEXT_ERROR,
            FAILED_TO_CREATE_SSL_CONNECTION,
            OPENSSL_ERROR,
            INVALID_QUERY_PARAMETER,
            UNSUPPORTED_PROTOCOL,
            INVALID_URI,
            AUTHORITY_PASSWORD_IS_EMPTY,
            AUTHORITY_USERNAME_IS_EMPTY,
            INVALID_PORT,
            INVALID_HOST,
            INVALID_URI_HEX_CODE,
            HOST_IS_EMPTY
        };

        Exception(const int &code, const std::string &what);

        int code();

        std::string what();

    private:
        int code_;
        std::string what_;
    };
}

#endif //OKHTTPFORK_EXCEPTION_HPP
