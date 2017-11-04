//
// Created by Good_Pudge.
//

#include "../include/Request.hpp"

namespace ohf {
    Request::Request(const Request::Builder *builder) :
            mCC(*builder->mCC),
            mMethod(builder->mMethod),
            mBody(*builder->mBody),
            mHeaders(builder->mHeaders.build()),
            mURL(*builder->mURL)
    {}

    RequestBody Request::body() {
        return mBody;
    }

    CacheControl Request::cacheControl() {
        return mCC;
    }

    std::string Request::header(const std::string &name) {
        return mHeaders.get(name);
    }

    std::vector<std::string> Request::headers(const std::string &name) {
        return mHeaders.values(name);
    }

    Headers Request::headers() {
        return mHeaders;
    }

    std::string Request::method() {
        return mMethod;
    }

    HttpURL Request::url() {
        return mURL;
    }

    bool Request::isHttps() {
        return mURL.isHttps();
    }

    Request::Builder Request::newBuilder() {
        return {this};
    }
}