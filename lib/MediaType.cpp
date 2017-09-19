//
// Created by Good_Pudge.
//

#include <vector>
#include "../include/MediaType.hpp"
#include "../util/include/string.hpp"
#include "../include/Exception.hpp"

using namespace ohf;

MediaType::MediaType(const std::string &str) {
    std::vector<std::string> values = util::string::split(str, "; ");
    // type / subtype
    std::vector<std::string> typeSubtype = util::string::split(values[0], "/");
    if (typeSubtype.size() == 2) {
        this->subtype_ = typeSubtype[1];
        this->type_ = typeSubtype[0];
    } else throw Exception(Exception::Code::INVALID_MIME_TYPE, "Invalid MIME type: " + values[0]);
    // boundary / charset
    this->boundary_ = "";
    this->charset_ = "";
    for (int i = 1; i < values.size(); i++) {
        std::string value = values[i];
        if (util::string::startsWith(value, "charset="))
            this->charset_ = value.substr(8, value.length());
        else if (util::string::startsWith(value, "boundary="))
            this->boundary_ = value.substr(9, value.length());
    }
}

MediaType::MediaType(const char *str) {
    *this = MediaType(std::string(str));
}

std::string MediaType::boundary() {
    return boundary_;
}

std::string MediaType::boundary(const std::string &defaultValue) {
    return boundary_.empty() ? defaultValue : boundary_;
}

std::string MediaType::charset() {
    return charset_;
}

std::string MediaType::charset(const std::string &defaultValue) {
    return charset_.empty() ? defaultValue : charset_;
}

bool MediaType::operator==(const MediaType &mediaType) {
    return this == &mediaType;
}

std::string MediaType::subtype() {
    return subtype_;
}

std::string MediaType::type() {
    return type_;
}