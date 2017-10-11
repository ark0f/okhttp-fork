//
// Created by Good_Pudge.
//

#include <sstream>
#include "../include/MultipartBody.hpp"
#include "../include/Exception.hpp"

namespace ohf {
    MediaType MultipartBody::MIXED = "multipart/mixed";
    MediaType MultipartBody::ALTERNATIVE = "multipart/alternative";
    MediaType MultipartBody::DIGEST = "multipart/digest";
    MediaType MultipartBody::PARALLEL = "multipart/parallel";
    MediaType MultipartBody::FORM = "multipart/form-data";

    std::string MultipartBody::boundary() {
        return mBoundary;
    }

    MultipartBody::Part MultipartBody::part(int index) {
        if (index > mParts.size())
            throw Exception(Exception::Code::OUT_OF_RANGE, "Out of range: " + index);
        return mParts[index];
    }

    std::vector<MultipartBody::Part> MultipartBody::parts() {
        return mParts;
    }

    int MultipartBody::size() {
        return mParts.size();
    }

    MediaType MultipartBody::type() {
        return mType;
    }

    MultipartBody::MultipartBody(const Builder *builder) :
            mBoundary(builder->mBoundary),
            mParts(builder->mParts),
            mType(builder->mType),
            RequestBody(
                    builder->mType.type().empty()
                    ? MediaType()
                    : builder->mType.type() + '/' + builder->mType.subtype() +
                      (builder->mType.charset().empty()
                       ? ""
                       : "; charset=" + builder->mType.charset()) +
                      "; boundary=" + builder->mBoundary,
                    std::vector<char>()) {
        struct Access {
            std::vector<char> content;
            MediaType mediaType;
        };

        std::stringstream ss;
        for (auto part : mParts) {
            ss << "--" << mBoundary << "\r\n";
            ss << part.mHeaders;

            std::stringstream contentType;
            contentType << part.mBody.contentType();
            std::string ct = contentType.str();
            if (!ct.empty()) ss << ct << "\r\n";

            ss << "\r\n";

            Access *access = (Access *) &part.mBody;
            std::vector<char> bodyContent = access->content;
            std::string contentStr(bodyContent.begin(), bodyContent.end());
            ss << contentStr << "\r\n";
        }
        ss << "--" << mBoundary << "--\r\n";
        ss << "\r\n";
        std::string readyContent = ss.str();
        content = std::vector<char>(readyContent.begin(), readyContent.end());
    }
}