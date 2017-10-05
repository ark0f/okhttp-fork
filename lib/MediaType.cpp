//
// Created by Good_Pudge.
//

#include <iostream>
#include <vector>
#include "../include/MediaType.hpp"
#include "../util/string.hpp"
#include "../include/Exception.hpp"

namespace ohf {
    MediaType::MediaType(const std::string &str) {
        std::vector<std::string> values = util::string::split(str, "; ");
        // type / subtype
        std::vector<std::string> typeSubtype = util::string::split(values[0], "/");
        if (typeSubtype.size() == 2) {
            this->mSubType = typeSubtype[1];
            this->mType = typeSubtype[0];
        } else throw Exception(Exception::Code::INVALID_MIME_TYPE, "Invalid MIME type: " + values[0]);
        // boundary / charset
        this->mBoundary = "";
        this->mCharset = "";
        for (int i = 1; i < values.size(); i++) {
            std::string value = values[i];
            if (util::string::startsWith(value, "charset="))
                this->mCharset = value.substr(8, value.length());
            else if (util::string::startsWith(value, "boundary="))
                this->mBoundary = value.substr(9, value.length());
        }
    }

    MediaType::MediaType(const char *str) : MediaType(std::string(str)) {
    }

    std::string MediaType::boundary() const {
        return mBoundary;
    }

    std::string MediaType::boundary(const std::string &defaultValue) const {
        return mBoundary.empty() ? defaultValue : mBoundary;
    }

    std::string MediaType::charset() const {
        return mCharset;
    }

    std::string MediaType::charset(const std::string &defaultValue) const {
        return mCharset.empty() ? defaultValue : mCharset;
    }

    std::string MediaType::subtype() const {
        return mSubType;
    }

    std::string MediaType::type() const {
        return mType;
    }

    bool MediaType::operator==(const MediaType &mediaType) {
        return mediaType.mBoundary == this->mBoundary
               || mediaType.mCharset == this->mCharset
               || mediaType.mBoundary == this->mBoundary
               || mediaType.mType == this->mType
               || mediaType.mSubType == this->mSubType;
    }

    std::ostream &operator<<(std::ostream &stream, const MediaType &mediaType) {
        stream << "Content-Type: " << mediaType.mType << '/' << mediaType.mSubType;

        std::string charset = mediaType.mCharset;
        if (!charset.empty())
            stream << "; charset=" << charset;

        std::string boundary = mediaType.mBoundary;
        if (!boundary.empty())
            stream << "; boundary=" << boundary;

        return stream;
    }
}