//
// Created by Good_Pudge.
//

#include <iostream>
#include <vector>
#include <sstream>
#include "../include/MediaType.hpp"
#include "../util/string.hpp"
#include "../include/Exception.hpp"

namespace ohf {
    MediaType::MediaType(const std::string &str) {
        std::vector<std::string> values = util::string::split(str, "; ");
        if (values.empty())
            throw Exception(Exception::Code::INVALID_CONTENT_TYPE_LINE, "Invalid Content-Type line: " + str);
        // type / subtype
        std::vector<std::string> typeSubtype = util::string::split(values[0], "/");
        if (typeSubtype.size() != 2)
            throw Exception(Exception::Code::INVALID_MIME_TYPE, "Invalid MIME type: " + values[0]);
        this->mSubType = typeSubtype[1];
        this->mType = typeSubtype[0];
        // boundary / charset
        for (int i = 1; i < values.size(); i++) {
            std::string value = values[i];
            if (util::string::startsWith(value, "charset=")) {
                std::string charset = value.substr(8, value.length());
                util::string::toLower(charset);
                this->mCharset = charset;
            } else if (util::string::startsWith(value, "boundary="))
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
        std::stringstream ss;

        std::string type = mediaType.mType;
        std::string subtype = mediaType.mSubType;
        if (!type.empty() && !subtype.empty())
            ss << type << '/' << subtype << "; ";

        std::string charset = mediaType.mCharset;
        if (!charset.empty())
            ss << "charset=" << charset << "; ";

        std::string boundary = mediaType.mBoundary;
        if (!boundary.empty())
            ss << "boundary=" << boundary << "; ";

        std::string str = ss.str();
        if (!str.empty()) {
            str.erase(str.length() - 2, 2);
            stream << "Content-Type: " << str;
        }

        return stream;
    }
}