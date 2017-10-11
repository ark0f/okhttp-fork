//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_REQUESTBODY_HPP
#define OKHTTPFORK_REQUESTBODY_HPP

#include <cstdio>
#include <vector>
#include "MediaType.hpp"

namespace ohf {
    class RequestBody {
    public:
        RequestBody(const MediaType &contentType, const char *content, size_t count);

        RequestBody(const MediaType &contentType, const std::string &content);

        RequestBody(const MediaType &contentType, const std::vector<char> &content);

        RequestBody(const MediaType &contentType, std::istream &stream);

        unsigned int contentLength();

        MediaType contentType();

    protected:
        std::vector<char> content;
        MediaType mediaType;
    };
}

#endif //OKHTTPFORK_REQUESTBODY_HPP
