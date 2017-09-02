//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_RESPONSE_HPP
#define OKHTTPFORK_RESPONSE_HPP

#include "ResponseBody.hpp"
#include "CacheControl.hpp"
#include "Challenge.hpp"
#include "Handshake.hpp"
#include "Headers.hpp"
#include "Request.hpp"
#include <vector>

namespace ohf {
    class Response {
    public:
        class Builder {
        };

        ResponseBody body();

        CacheControl cacheControl();

        Response cacheResponse();

        std::vector<Challenge> challenges();

        void close();

        int code();

        Handshake handshake();

        const char *header(const char *name);

        const char *header(const char *name, const char *default_value);

        Headers headers();

        std::vector<const char *> headers(const char *name);

        bool isRedirect();

        bool isSuccessful();

        const char *message();

        Response networkResponse();

        Builder newBuilder();

        ResponseBody peekBody(long byte_count);

        Response priorBody();

        long receivedResponseAtMillis();

        Request request();

        long sentRequestAtMillis();
    };
}


#endif //OKHTTPFORK_RESPONSE_HPP
