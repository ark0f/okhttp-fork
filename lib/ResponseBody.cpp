//
// Created by Good_Pudge.
//

#include <sstream>
#include "../include/ResponseBody.hpp"

using namespace ohf;

ResponseBody::ResponseBody(const MediaType &mediaType, const char *content) {
    this->mediaType = mediaType;
    this->content = std::string(content);
}

ResponseBody::ResponseBody(const MediaType &mediaType, const std::string &content) {
    this->mediaType = mediaType;
    this->content = content;
}

char *ResponseBody::bytes() {
    char *chars = new char[content.length() + 1];
    strcpy(chars, content.c_str());
    return chars;
}

unsigned int ResponseBody::contentLength() {
    return content.length();
}

MediaType ResponseBody::contentType() {
    return mediaType;
}

std::string ResponseBody::string() {
    return content;
}