//
// Created by Good_Pudge.
//

#include <iostream>
#include <cstring>
#include <iterator>
#include <ohf/ResponseBody.hpp>
#include "util/util.hpp"

namespace ohf {
    ResponseBody::ResponseBody(const MediaType &mediaType, const char *content, size_t count, StreamBuf *buffer) :
            mediaType(mediaType),
            content(content, content + count),
            is(std::make_shared<std::istream>(buffer))
    {
        buffer->vector(this->content);
    }

    ResponseBody::ResponseBody(const MediaType &mediaType, const std::vector<Int8> &content, StreamBuf *buffer) :
            mediaType(mediaType),
            content(content),
            is(std::make_shared<std::istream>(buffer))
    {
        buffer->vector(this->content);
    }

    ResponseBody::ResponseBody(const MediaType &mediaType, const std::string &content, StreamBuf *buffer) :
            mediaType(mediaType),
            content(content.begin(), content.end()),
            is(std::make_shared<std::istream>(buffer))
    {
        buffer->vector(this->content);
    }

    ResponseBody::ResponseBody(const MediaType &mediaType, std::istream &stream, StreamBuf *buffer) :
            mediaType(mediaType),
            content(util::readStream(stream)),
            is(std::make_shared<std::istream>(buffer))
    {
        buffer->vector(this->content);
    }

    std::vector<Int8> ResponseBody::bytes() {
        return content;
    }

    std::string ResponseBody::string() {
        return std::string(content.begin(), content.end());
    }

    std::istream &ResponseBody::stream() {
        return *is;
    }

    Uint64 ResponseBody::contentLength() {
        return content.size();
    }

    MediaType ResponseBody::contentType() {
        return mediaType;
    }
}