//
// Created by Good_Pudge.
//

#include <cstring>
#include <ohf/Request.hpp>
#include <ohf/Exception.hpp>

namespace ohf {
    Request::Builder::~Builder() {
        delete mCC;
        delete mURL;
        delete mBody;
    }

    Request Request::Builder::build() {
        if(mMethod.empty())
            throw Exception(Exception::Code::METHOD_IS_NOT_NAMED, "Method is not named: ");
        if(mURL == nullptr)
            throw Exception(Exception::Code::URL_IS_NOT_NAMED, "URL is not named: ");
        if(mCC == nullptr)
            mCC = new CacheControl();
        if(mBody == nullptr)
            mBody = new RequestBody();

        return {this};
    }

    Request::Builder& Request::Builder::cacheControl(const CacheControl &cacheControl) {
        mCC = new CacheControl(cacheControl);
        std::string value = mCC->toString();
        if(value.empty()) return removeHeader("Cache-Control");
        return header("Cache-Control", value);
    }

    Request::Builder& Request::Builder::delete_() {
        mMethod = "DELETE";
        mBody = nullptr;
        return *this;
    }

    Request::Builder& Request::Builder::delete_(const RequestBody &body) {
        mMethod = "DELETE";
        mBody = body.clone();

        return *this;
    }

    Request::Builder& Request::Builder::get() {
        mMethod = "GET";
        mBody = nullptr;

        return *this;
    }

    Request::Builder& Request::Builder::head() {
        mMethod = "HEAD";
        mBody = nullptr;

        return *this;
    }

    Request::Builder& Request::Builder::patch(const RequestBody &body) {
        mMethod = "PATCH";
        mBody = body.clone();

        return *this;
    }

    Request::Builder& Request::Builder::post(const RequestBody &body) {
        mMethod = "POST";
        mBody = body.clone();

        return *this;
    }

    Request::Builder& Request::Builder::put(const RequestBody &body) {
        mMethod = "PUT";
        mBody = body.clone();

        return *this;
    }

    Request::Builder& Request::Builder::method(const std::string &method) {
        mMethod = method;
        mBody = nullptr;

        return *this;
    }

    Request::Builder& Request::Builder::method(const std::string &method, const RequestBody &body) {
        mMethod = method;
        mBody = body.clone();

        return *this;
    }

    Request::Builder& Request::Builder::addHeader(const std::string &name, const std::string &value) {
        mHeaders.add(name, value);
        return *this;
    }

    Request::Builder& Request::Builder::header(const std::string &name, const std::string &value) {
        mHeaders.set(name, value);
        return *this;
    }

    Request::Builder& Request::Builder::headers(const Headers &headers) {
        mHeaders = headers.newBuilder();
        return *this;
    }

    Request::Builder& Request::Builder::removeHeader(const std::string &name) {
        mHeaders.removeAll(name);
        return *this;
    }

    Request::Builder& Request::Builder::url(const HttpURL &url) {
        mURL = new HttpURL(url);
        return *this;
    }

    Request::Builder::Builder(Request *request) :
            mMethod(request->mMethod),
            mHeaders(request->mHeaders.newBuilder()),
            mCC(new CacheControl(request->mCC)),
            mURL(new HttpURL(request->mURL)),
            mBody(new RequestBody(request->mBody))
    {}
}