//
// Created by Good_Pudge.
//

#include <vector>
#include "../include/MediaType.hpp"
#include "../util/string.hpp"
#include "../include/Exception.hpp"

using namespace ohf;

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

std::string MediaType::boundary() {
    return mBoundary;
}

std::string MediaType::boundary(const std::string &defaultValue) {
    return mBoundary.empty() ? defaultValue : mBoundary;
}

std::string MediaType::charset() {
    return mCharset;
}

std::string MediaType::charset(const std::string &defaultValue) {
    return mCharset.empty() ? defaultValue : mCharset;
}

bool MediaType::operator==(const MediaType &mediaType) {
    return this == &mediaType;
}

std::string MediaType::subtype() {
    return mSubType;
}

std::string MediaType::type() {
    return mType;
}