//
// Created by Good_Pudge.
//

#include <iostream>
#include <cstring>
#include <iterator>
#include <ohf/ResponseBody.hpp>
#include "util/util.hpp"

namespace ohf {
    ResponseBody::ResponseBody(const MediaType &mediaType, const char *content, size_t count, std::streambuf *buffer) :
            ResponseBody(mediaType, std::vector<Int8>(content, content + count), buffer)
    {}

    ResponseBody::ResponseBody(const MediaType &mediaType, const std::vector<Int8> &content, std::streambuf *buffer) :
            mediaType(mediaType),
            content(content),
            is(std::make_shared<std::istream>(buffer))
    {}

    ResponseBody::ResponseBody(const MediaType &mediaType, const std::string &content, std::streambuf *buffer) :
            ResponseBody(mediaType, std::vector<Int8>(content.begin(), content.end()), buffer)
    {}

    ResponseBody::ResponseBody(const MediaType &mediaType, std::istream &stream, std::streambuf *buffer) :
            ResponseBody(mediaType, util::readStream(stream), buffer)
    {}

    std::vector<Int8> ResponseBody::bytes() const {
        return content;
    }

    std::string ResponseBody::string() const {
        return {content.begin(), content.end()};
    }

    std::istream &ResponseBody::stream() const {
        return *is;
    }

    Uint64 ResponseBody::contentLength() const {
        return content.size();
    }

    MediaType ResponseBody::contentType() const {
        return mediaType;
    }
}