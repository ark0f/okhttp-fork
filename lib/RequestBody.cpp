//
// Created by Good_Pudge.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <ohf/RequestBody.hpp>
#include "util/util.hpp"

namespace ohf {
    RequestBody::RequestBody() : mediaType(MediaType()) {}

    RequestBody::RequestBody(const MediaType &contentType, const char *content, size_t count) :
            mediaType(contentType),
            content(std::vector<Int8>(content, content + count))
    {}

    RequestBody::RequestBody(const MediaType &contentType, const std::string &content) :
            mediaType(contentType),
            content(content.begin(), content.end())
    {}

    RequestBody::RequestBody(const MediaType &contentType, const std::vector<Int8> &content) :
            mediaType(contentType),
            content(content) {}

    RequestBody::RequestBody(const MediaType &contentType, std::istream &stream) :
            mediaType(contentType),
            content(util::readStream(stream))
    {}

    Uint32 RequestBody::contentLength() {
        return content.size();
    }

    MediaType RequestBody::contentType() {
        return mediaType;
    }

    RequestBody* RequestBody::clone() const {
        return new RequestBody(*this);
    }
}
