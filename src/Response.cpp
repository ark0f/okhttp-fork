//
// Created by Good_Pudge.
//

#include <istream>
#include <ohf/Response.hpp>
#include <sstream>
#include <ohf/Exception.hpp>
#include "util/string.hpp"

namespace {
    inline void invalidChallenge(const std::string &name, const std::string &value) {
        throw ohf::Exception(ohf::Exception::Code::INVALID_CHALLENGE, "Invalid challenge: " + name + ": " + value);
    }

    std::string getByName(const std::string &name, const std::string &value) {
        std::string::size_type offset;
        if((offset = value.find(name)) != std::string::npos) {
            offset += name.length();

            // check first quote
            if(value[offset++] != '"') {
                return {};
            }

            auto start = offset;

            // check second quote
            if((offset = value.find('"', offset)) == std::string::npos) {
                return {};
            }

            return value.substr(start, offset - start);
        }

        return {};
    }
}

namespace ohf {
    Protocol Response::protocol() const {
        return mProtocol;
    }

    Int32 Response::code() const {
        return mCode;
    }

    std::string Response::message() const {
        return mMessage;
    }

    ResponseBody Response::body() const {
        return mBody;
    }

    ResponseBody Response::peekBody(Uint64 byteCount) const {
        auto content = mBody.bytes();
        return {mBody.contentType(),
                std::vector<Int8>(content.begin(), content.begin() + byteCount),
                mBody.stream().rdbuf()};
    }

    Request Response::request() const {
        return mRequest;
    }

    ssl::Handshake Response::handshake() const {
        return mHandshake;
    }

    std::string Response::header(const std::string &name) const {
        return mHeaders.get(name);
    }

    std::string Response::header(const std::string &name, const std::string &defaultValue) const {
        std::string header = mHeaders.get(name);
        return header.empty() ? defaultValue : header;
    }

    std::vector<std::string> Response::headers(const std::string &name) const {
        return mHeaders.values(name);
    }

    Headers Response::headers() const {
        return mHeaders;
    }

    TimeUnit Response::sentRequest() const {
        return mSent;
    }

    TimeUnit Response::receivedResponse() const {
        return mReceived;
    }

    CacheControl Response::cacheControl() const {
        return CacheControl(mHeaders);
    }

    std::vector<ssl::Challenge> Response::challenges() const {
        std::vector<ssl::Challenge> challenges;
        for(const auto &header : mHeaders) {
            std::string name = header.first;
            std::string value = header.second;

            if(name == "WWW-Authenticate" || name == "Proxy-Authenticate") {
                auto offset = value.find_first_of(' ');
                if(offset == std::string::npos) {
                    invalidChallenge(name, value);
                }

                std::string scheme(value, 0, offset);
                std::string realm = getByName("realm=", value);
                std::string charset = getByName("charset=", value);

                if(realm.empty()) {
                    invalidChallenge(name, value);
                }

                challenges.emplace_back(scheme, realm, charset);
            }
        }

        return challenges;
    }

    bool Response::isRedirect() const {
        return mCode >= 300 && mCode <= 308;
    }

    bool Response::isSuccessful() const {
        return mCode >= 200 && mCode < 300;
    }

    Response::Builder Response::newBuilder() {
        return {this};
    }

    Response::Response(const Builder *builder) :
            mProtocol(builder->mProtocol),
            mCode(builder->mCode),
            mMessage(builder->mMessage),
            mBody(*builder->mBody),
            mRequest(*builder->mRequest),
            mHandshake(builder->mHandshake),
            mHeaders(builder->mHeaders.build()),
            mSent(builder->mSent),
            mReceived(builder->mReceived)
    {}
}