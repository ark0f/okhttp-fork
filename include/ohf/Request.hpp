//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_REQUEST_HPP
#define OKHTTPFORK_REQUEST_HPP

#include <memory>
#include "RequestBody.hpp"
#include "CacheControl.hpp"
#include "HttpURL.hpp"

namespace ohf {
    class Request {
    public:
        class Builder {
        public:
            Builder() = default;

            ~Builder();

            Request build();

            Builder& cacheControl(const CacheControl &cacheControl);

            Builder& delete_();

            Builder& delete_(const RequestBody &body);

            Builder& get();

            Builder& head();

            Builder& patch(const RequestBody &body);

            Builder& post(const RequestBody &body);

            Builder& put(const RequestBody &body);

            Builder& method(const std::string &method);

            Builder& method(const std::string &method, const RequestBody &body);

            Builder& addHeader(const std::string &name, const std::string &value);

            Builder& header(const std::string &name, const std::string &value);

            Builder& headers(const Headers &headers);

            Builder& removeHeader(const std::string &name);

            Builder& url(const HttpURL &url);
        private:
            Builder(Request *request);

            CacheControl *mCC;
            std::string mMethod;
            RequestBody *mBody;
            Headers::Builder mHeaders;
            HttpURL *mURL;

            friend class ohf::Request;
        };

        RequestBody body() const;

        CacheControl cacheControl() const;

        std::string header(const std::string &name) const;

        std::vector<std::string> headers(const std::string &name) const;

        Headers headers() const;

        std::string method() const;

        HttpURL url() const;

        bool isHttps() const;

        Builder newBuilder();

    private:
        Request(const Builder *builder);

        CacheControl mCC;
        std::string mMethod;
        RequestBody mBody;
        Headers mHeaders;
        HttpURL mURL;
    };
}

#endif //OKHTTPFORK_REQUEST_HPP
