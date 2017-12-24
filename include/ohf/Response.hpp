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
#include "TimeUnit.hpp"
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

        const std::string header(const std::string &name);

        const std::string header(const std::string &name, const std::string &default_value);

        Headers headers();

        std::vector<std::string> headers(const std::string &name);

        bool isRedirect();

        bool isSuccessful();

        std::string message();

        Response networkResponse();

        Builder newBuilder();

        ResponseBody peekBody(long byte_count);

        Response priorBody();

        TimeUnit receivedResponse();

        Request request();

        TimeUnit sentRequest();
    };
}


#endif //OKHTTPFORK_RESPONSE_HPP
