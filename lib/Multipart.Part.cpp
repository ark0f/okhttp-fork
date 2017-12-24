//
// Created by Good_Pudge.
//

#include "../include/ohf/MultipartBody.hpp"
#include "../include/ohf/Exception.hpp"

namespace ohf {
    std::string handleQuotedString(const std::string &str) {
        std::string tmp;
        for (const char &c : str) {
            switch (c) {
                case '\n':
                    tmp += "%A0";
                    break;
                case '\r':
                    tmp += "%0D";
                    break;
                case '"':
                    tmp += "%22";
                    break;
                default:
                    tmp.push_back(c);
                    break;
            }
        }
        return tmp;
    }

    MultipartBody::Part::Part(const std::string &name, const std::string &value) :
            mHeaders(Headers::Builder()
                             .add("Content-Disposition", "form-data; name=\"" + handleQuotedString(name) + '"')
                             .build()),
            mBody(RequestBody(MediaType(), value)) {}

    MultipartBody::Part::Part(const std::string &name, const std::string &filename, const RequestBody &body) :
            mHeaders(Headers::Builder()
                             .add("Content-Disposition",
                                  "form-data; name=\"" + handleQuotedString(name) +
                                  "\"; filename=\"" + handleQuotedString(filename) + '"')
                             .build()),
            mBody(body) {}

    MultipartBody::Part::Part(const Headers &headers, const RequestBody &body) :
            mHeaders(headers),
            mBody(body) {
        bool cdExists = false;
        for (const auto &name : mHeaders.names()) {
            if (name == "content-type")
                throw Exception(Exception::Code::UNEXPECTED_HEADER, "Unexpected header: Content-Type");
            else if (name == "content-length")
                throw Exception(Exception::Code::UNEXPECTED_HEADER, "Unexpected header: Content-Length");
            else if (name == "content-disposition")
                cdExists = true;
        }
        if (!cdExists)
            mHeaders = mHeaders.newBuilder()
                    .add("Content-Disposition", "form-data")
                    .build();
    }

    MultipartBody::Part::Part(const RequestBody &body) : MultipartBody::Part::Part(Headers::Builder().build(), body) {}

    RequestBody MultipartBody::Part::body() const {
        return mBody;
    }

    Headers MultipartBody::Part::headers() const {
        return mHeaders;
    }
}