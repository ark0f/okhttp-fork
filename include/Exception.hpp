//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_EXCEPTION_HPP
#define OKHTTPFORK_EXCEPTION_HPP

#include <string>

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
            FAILED_TO_SHUTDOWN_SOCKET,
            OPENSSL_INIT_ERROR,
            OPENSSL_CREATE_CONTEXT_ERROR,
            FAILED_TO_CREATE_SSL_CONNECTION,
            OPENSSL_ERROR,
            INVALID_QUERY_PARAMETER,
            INVALID_URI,
            INVALID_PORT,
            INVALID_HOST,
            INVALID_URI_HEX_CODE,
            HOST_IS_EMPTY,
            OUT_OF_RANGE,
            INVALID_COOKIE_LINE,
            INVALID_COOKIE_PARAMETER,
            INVALID_MAX_AGE
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
