//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_EXCEPTION_HPP
#define OKHTTPFORK_EXCEPTION_HPP

#include <string>

namespace ohf {
    class Exception : public std::exception {
    public:
        enum class Code {
            HEADER_NOT_EXISTS,
            INVALID_HEADER_LINE,
            INVALID_MIME_TYPE,
            FAILED_TO_READ_STREAM,
            FAILED_TO_CREATE_SOCKET,
            UNKNOWN_HOST,
            FAILED_TO_CREATE_CONNECTION,
            FAILED_TO_SEND_DATA,
            FAILED_TO_RECEIVE_DATA,
            FAILED_TO_SHUTDOWN_SOCKET,
            SSL_CREATE_ERROR,
            SSL_CONTEXT_CREATE_ERROR,
            SSL_CONNECTION_CREATE_ERROR,
            SSL_ERROR,
            INVALID_QUERY_PARAMETER,
            INVALID_URI,
            INVALID_PORT,
            INVALID_HOST,
            INVALID_URI_HEX_CODE,
            HOST_IS_EMPTY,
            OUT_OF_RANGE,
            INVALID_COOKIE_LINE,
            INVALID_COOKIE_PARAMETER,
            INVALID_MAX_AGE,
            INVALID_S_MAX_AGE,
            INVALID_IP,
            INVALID_MAX_STALE,
            INVALID_MIN_FRESH
        };

        Exception(Code code, const std::string &what) noexcept;

        Code code() const noexcept;

        std::string message() const noexcept;

        const char *what() const noexcept override;

        friend std::ostream &operator<<(std::ostream &stream, const Exception &e);
    private:
        Code m_code;
        std::string m_what;
    };
}

#endif //OKHTTPFORK_EXCEPTION_HPP
