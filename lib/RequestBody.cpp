//
// Created by Good_Pudge.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "../include/RequestBody.hpp"
#include "../util/util.hpp"

using namespace ohf;

unsigned int RequestBody::contentLength() {
    return content.length();
}

MediaType RequestBody::contentType() {
    return mediaType;
}

RequestBody::RequestBody(const MediaType &contentType, const char *content) {
    this->mediaType = contentType;
    this->content = content;
}

RequestBody::RequestBody(const MediaType &contentType, const char *content, int offset, int byteCount) {
    this->mediaType = contentType;
    for (int i = offset; i < offset + byteCount; i++) {
        this->content += (content[i]);
    }
}

RequestBody::RequestBody(const MediaType &contentType, const std::string &content) {
    this->mediaType = contentType;
    this->content = content;
}

RequestBody::RequestBody(const MediaType &contentType, std::istream &stream) {
    this->mediaType = contentType;

    std::vector<char> buffer = util::readStream(stream);
    this->content = std::string(buffer.begin(), buffer.end());
}
