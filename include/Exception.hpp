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
            INVALID_HEADER_LINE,
            INVALID_MIME_TYPE,
            FAILED_TO_READ_STREAM,
            FAILED_TO_CREATE_SOCKET,
            UNKNOWN_HOST,
            FAILED_TO_CREATE_CONNECTION,
            NO_DATA_TO_SEND,
            FAILED_TO_SEND_DATA,
            FAILED_TO_RECEIVE_DATA,
            FAILED_TO_BIND_SOCKET,
            DATAGRAM_PACKET_IS_TOO_BIG,
            SSL_CREATE_ERROR,
            SSL_CONTEXT_CREATE_ERROR,
            SSL_CONNECTION_CREATE_ERROR,
            SSL_ERROR,
            INVALID_QUERY_PARAMETER,
            INVALID_URI,
            INVALID_PORT,
            INVALID_URI_HEX_CODE,
            HOST_IS_EMPTY,
            OUT_OF_RANGE,
            INVALID_COOKIE_LINE,
            INVALID_COOKIE_NAME_VALUE,
            INVALID_MAX_AGE,
            INVALID_S_MAX_AGE,
            INVALID_IP,
            INVALID_MAX_STALE,
            INVALID_MIN_FRESH,
            UNEXPECTED_HEADER,
            INVALID_CONTENT_TYPE_LINE,
            HEADER_NAME_IS_EMPTY,
            HEADER_VALUE_IS_EMPTY,
            METHOD_IS_NOT_NAMED,
            URL_IS_NOT_NAMED
        };

        Exception(const Code &code, const std::string &what) noexcept;

        Code code() const noexcept;

        std::string message() const noexcept;

        const char *what() const noexcept override;

    private:
        Code m_code;
        std::string m_what;
    };
}

#endif //OKHTTPFORK_EXCEPTION_HPP
