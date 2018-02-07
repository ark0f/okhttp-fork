//
// Created by Good_Pudge.
//

#include <ohf/Response.hpp>
#include <ohf/Exception.hpp>

namespace ohf {
    Response::Builder::Builder() :
            mProtocol(Protocol::HTTP_1_1),
            mCode(200),
            mMessage("OK"),
            mSent(TimeUnit::MINUS_ONE_SECOND),
            mReceived(TimeUnit::MINUS_ONE_SECOND)
    {}

    Response::Builder::~Builder() {
        delete mBody;
        delete mRequest;
    }

    Response::Builder& Response::Builder::protocol(Protocol protocol) {
        mProtocol = protocol;
        return *this;
    }

    Response::Builder& Response::Builder::code(Int32 code) {
        mCode = code;
        return *this;
    }

    Response::Builder& Response::Builder::message(const std::string &message) {
        mMessage = message;
        return *this;
    }

    Response::Builder& Response::Builder::body(const ResponseBody &body) {
        mBody = new ResponseBody(body);
        return *this;
    }

    Response::Builder& Response::Builder::request(const Request &request) {
        mRequest = new Request(request);
        return *this;
    }

    Response::Builder& Response::Builder::handshake(const ssl::Handshake &handshake) {
        mHandshake = handshake;
        return *this;
    }

    Response::Builder& Response::Builder::addHeader(const std::string &name, const std::string &value) {
        mHeaders.add(name, value);
        return *this;
    }

    Response::Builder& Response::Builder::header(const std::string &name, const std::string &value) {
        mHeaders.set(name, value);
        return *this;
    }

    Response::Builder& Response::Builder::removeHeader(const std::string &name) {
        mHeaders.removeAll(name);
        return *this;
    }

    Response::Builder& Response::Builder::headers(const Headers &headers) {
        mHeaders = headers.newBuilder();
        return *this;
    }

    Response::Builder& Response::Builder::sentRequest(const TimeUnit &time) {
        mSent = time;
        return *this;
    }

    Response::Builder& Response::Builder::receivedResponse(const TimeUnit &time) {
        mReceived = time;
        return *this;
    }

    Response Response::Builder::build() {
        if(mBody == nullptr) {
            throw Exception(Exception::Code::RESPONSE_BODY_IS_NOT_SPECIFIED, "Response body is not specified");
        }

        if(mRequest == nullptr) {
            throw Exception(Exception::Code::REQUEST_IS_NOT_SPECIFIED, "Request is not specified");
        }

        return {this};
    }

    Response::Builder::Builder(const Response *response) :
            mProtocol(response->mProtocol),
            mCode(response->mCode),
            mMessage(response->mMessage),
            mBody(new ResponseBody(response->mBody)),
            mRequest(new Request(response->mRequest)),
            mHandshake(response->mHandshake),
            mHeaders(response->mHeaders.newBuilder()),
            mSent(response->mSent),
            mReceived(response->mReceived)
    {}
}