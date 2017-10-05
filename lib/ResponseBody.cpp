//
// Created by Good_Pudge.
//

#include <iostream>
#include <cstring>
#include "../include/ResponseBody.hpp"
#include "../util/util.hpp"

namespace ohf {
    ResponseBody::ResponseBody(const MediaType &mediaType, const char *content, size_t count) :
            mediaType(mediaType),
            is(std::make_shared<std::istream>(new StreamBuf(this))) {
        for (size_t i = 0; i < count; i++)
            this->content.push_back(content[i]);
    }

    ResponseBody::ResponseBody(const MediaType &mediaType, const std::vector<char> &content) :
            mediaType(mediaType),
            content(content),
            is(std::make_shared<std::istream>(new StreamBuf(this))) {}

    ResponseBody::ResponseBody(const MediaType &mediaType, const std::string &content) :
            mediaType(mediaType),
            is(std::make_shared<std::istream>(new StreamBuf(this))),
            content(content.begin(), content.end()) {}

    ResponseBody::ResponseBody(const MediaType &mediaType, std::istream &stream) :
            mediaType(mediaType),
            is(std::make_shared<std::istream>(new StreamBuf(this))),
            content(util::readStream(stream)) {}

    std::vector<char> ResponseBody::bytes() {
        return content;
    }

    std::istream &ResponseBody::stream() {
        return *is;
    }

    unsigned int ResponseBody::contentLength() {
        return content.size();
    }

    MediaType ResponseBody::contentType() {
        return mediaType;
    }

    std::string ResponseBody::string() {
        return std::string(content.begin(), content.end());
    }
}