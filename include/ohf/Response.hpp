//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_RESPONSE_HPP
#define OKHTTPFORK_RESPONSE_HPP

#include <ohf/Protocol.hpp>
#include <ohf/Request.hpp>
#include <ohf/ResponseBody.hpp>
#include <ohf/ssl/Challenge.hpp>
#include <ohf/ssl/Handshake.hpp>

namespace ohf {
    class Response {
    public:
        class Builder {
        public:
            Builder();

            ~Builder();

            Builder& protocol(Protocol protocol);

            Builder& code(Int32 code);

            Builder& message(const std::string &message);

            Builder& body(const ResponseBody &body);

            Builder& request(const Request &request);

            Builder& handshake(const ssl::Handshake &handshake);

            //Builder& cacheResponse(const Response &cacheResponse);

            //Builder& networkResponse(const Response &networkResponse);

            //Builder& priorResponse(const Response &priorResponse);

            Builder& addHeader(const std::string &name, const std::string &value);

            Builder& header(const std::string &name, const std::string &value);

            Builder& removeHeader(const std::string &name);

            Builder& headers(const Headers &headers);

            Builder& sentRequest(const TimeUnit &time);

            Builder& receivedResponse(const TimeUnit &time);

            Response build();

        private:
            Builder(const Response *response);

            Protocol mProtocol;
            Int32 mCode;
            std::string mMessage;

            ResponseBody *mBody;
            Request *mRequest;
            ssl::Handshake mHandshake;

            //const Response &mCacheResponse;
            //const Response &mNetworkResponse;
            //const Response &mPriorResponse;

            Headers::Builder mHeaders;

            TimeUnit mSent;
            TimeUnit mReceived;

            friend class ohf::Response;
        };

        Protocol protocol() const;

        Int32 code() const;

        std::string message() const;

        ResponseBody body() const;

        ResponseBody peekBody(Uint64 byteCount) const;

        Request request() const;

        ssl::Handshake handshake() const;

        //Response cacheResponse();

        //Response networkResponse();

        //Response priorResponse();

        std::string header(const std::string &name) const;

        std::string header(const std::string &name, const std::string &defaultValue) const;

        std::vector<std::string> headers(const std::string &name) const;

        Headers headers() const;

        TimeUnit sentRequest() const;

        TimeUnit receivedResponse() const;

        CacheControl cacheControl() const;

        std::vector<ssl::Challenge> challenges() const;

        bool isRedirect() const;

        bool isSuccessful() const;

        Builder newBuilder();

    private:
        Response(const Builder *builder);

        Protocol mProtocol;
        Int32 mCode;
        std::string mMessage;

        ResponseBody mBody;
        Request mRequest;
        ssl::Handshake mHandshake;

        Headers mHeaders;

        TimeUnit mSent;
        TimeUnit mReceived;
    };
}


#endif //OKHTTPFORK_RESPONSE_HPP
