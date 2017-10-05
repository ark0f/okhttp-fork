//
// Created by Good_Pudge.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "../include/RequestBody.hpp"
#include "../util/util.hpp"

namespace ohf {
    unsigned int RequestBody::contentLength() {
        return content.size();
    }

    MediaType RequestBody::contentType() {
        return mediaType;
    }

    RequestBody::RequestBody(const MediaType &contentType, const char *content, size_t count) :
            mediaType(contentType) {
        for (size_t i = 0; i < count; i++)
            this->content.push_back(content[i]);
    }

    RequestBody::RequestBody(const MediaType &contentType, const std::string &content) :
            mediaType(contentType),
            content(content.begin(), content.end()) {}

    RequestBody::RequestBody(const MediaType &contentType, const std::vector<char> &content) :
            mediaType(contentType),
            content(content) {}

    RequestBody::RequestBody(const MediaType &contentType, std::istream &stream) :
            mediaType(contentType),
            content(util::readStream(stream)) {}
}
