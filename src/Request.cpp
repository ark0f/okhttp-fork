//
// Created by Good_Pudge.
//

#include <ohf/Request.hpp>

namespace ohf {
    Request::Request(const Request::Builder *builder) :
            mCC(*builder->mCC),
            mMethod(builder->mMethod),
            mBody(*builder->mBody),
            mHeaders(builder->mHeaders.build()),
            mURL(*builder->mURL)
    {}

    RequestBody Request::body() const {
        return mBody;
    }

    CacheControl Request::cacheControl() const {
        return mCC;
    }

    std::string Request::header(const std::string &name) const {
        return mHeaders.get(name);
    }

    std::vector<std::string> Request::headers(const std::string &name) const {
        return mHeaders.values(name);
    }

    Headers Request::headers() const {
        return mHeaders;
    }

    std::string Request::method() const {
        return mMethod;
    }

    HttpURL Request::url() const {
        return mURL;
    }

    bool Request::isHttps() const {
        return mURL.isHttps();
    }

    Request::Builder Request::newBuilder() {
        return {this};
    }
}