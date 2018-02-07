//
// Created by Good_Pudge.
//

#include <sstream>
#include <ohf/MultipartBody.hpp>
#include <ohf/Exception.hpp>
#include <ohf/RangeException.hpp>

namespace ohf {
    MediaType MultipartBody::MIXED = "multipart/mixed";
    MediaType MultipartBody::ALTERNATIVE = "multipart/alternative";
    MediaType MultipartBody::DIGEST = "multipart/digest";
    MediaType MultipartBody::PARALLEL = "multipart/parallel";
    MediaType MultipartBody::FORM = "multipart/form-data";

    std::string MultipartBody::boundary() {
        return mBoundary;
    }

    MultipartBody::Part MultipartBody::part(Uint64 index) {
        if (index >= mParts.size())
            throw RangeException(index);
        return mParts[index];
    }

    std::vector<MultipartBody::Part> MultipartBody::parts() {
        return mParts;
    }

    Uint64 MultipartBody::size() {
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
                    builder->mType.type().empty() // original MediaType
                    ? FORM
                    : MediaType(builder->mType.type() + '/' + builder->mType.subtype() +
                        (builder->mType.charset().empty()
                        ? std::string()
                        : "; charset=" + builder->mType.charset()) + "; boundary=" + builder->mBoundary),
                    std::vector<char>())
    {
        std::stringstream ss;
        for (auto part : mParts) {
            ss << "--" << mBoundary << "\r\n";
            ss << part.mHeaders;

            std::string ct = part.mBody.contentType().toString();
            if (!ct.empty()) ss << "Content-Type: " << ct << "\r\n";

            ss << "\r\n";

            std::vector<char> bodyContent = part.mBody.content;
            ss.write(bodyContent.data(), bodyContent.size());

            ss << "\r\n";
        }
        ss << "--" << mBoundary << "--";

        std::string readyContent = ss.str();
        content = {readyContent.begin(), readyContent.end()};
    }
}
