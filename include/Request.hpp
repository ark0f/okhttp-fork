//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_REQUEST_HPP
#define OKHTTPFORK_REQUEST_HPP

#include "RequestBody.hpp"
#include "CacheControl.hpp"
#include "HttpURL.hpp"

namespace ohf {
    class Request {
    public:
        class Builder {
        public:
            void addHeader(const char *name, const char *value);

            Request build();

            void cacheControl(const CacheControl &cacheControl);

            void del();

            void del(const RequestBody &body);

            void get();

            void head();

            void header(const char *name, const char *value);

            void headers(const Headers &headers);

            void method(const char *method, const RequestBody &body);

            void patch(const RequestBody &body);

            void post(const RequestBody &body);

            void put(const RequestBody &body);

            void removeHeader(const char *name);

            // Builder tag(const Object &obj);
            void url(const HttpUrl &url);

            void url(const char *url);
        };

        RequestBody &body();

        CacheControl &cacheControl();

        const char *header(const char *name);

        Headers &headers();

        // std::vector<const char *> headers(const char *name);
        bool isHttps();

        const char *method();

        Builder newBuilder();

        // Object tag();
        HttpUrl url();
    };
}

#endif //OKHTTPFORK_REQUEST_HPP
