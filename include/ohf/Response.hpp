//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_RESPONSE_HPP
#define OKHTTPFORK_RESPONSE_HPP

#include <ohf/Protocol.hpp>
#include <ohf/Request.hpp>
#include <ohf/ResponseBody.hpp>
#include <ohf/Challenge.hpp>
#include <ohf/ssl/Handshake.hpp>

namespace ohf {
    class Response {
    public:
        class Builder {
        public:
            Response build();

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

        private:
            Protocol mProtocol;
            Int32 mCode;
            std::string mMessage;

            ResponseBody mBody;
            Request mRequest;
            ssl::Handshake mHandshake;

            //const Response &mCacheResponse;
            //const Response &mNetworkResponse;
            //const Response &mPriorResponse;

            Headers mHeaders;

            TimeUnit mSent;
            TimeUnit mReceived;
        };

        Protocol protocol() const;

        Int32 code() const;

        std::string message() const;

        ResponseBody body();

        ResponseBody peekBody(Uint64 byteCount);

        Request request();

        ssl::Handshake handshake();

        //Response cacheResponse();

        //Response networkResponse();

        //Response priorResponse();

        std::string header(const std::string &name);

        std::string header(const std::string &name, const std::string &defaultValue);

        std::vector<std::string> headers(const std::string &name);

        Headers headers();

        TimeUnit sentRequest();

        TimeUnit receivedResponse();

        CacheControl cacheControl();

        std::vector<Challenge> challenges();

        void close();

        bool isRedirect();

        bool isSuccessful();

        Builder newBuilder();
    };
}


#endif //OKHTTPFORK_RESPONSE_HPP
