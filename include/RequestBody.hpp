//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_REQUESTBODY_HPP
#define OKHTTPFORK_REQUESTBODY_HPP

#include <cstdio>
#include "MediaType.hpp"

namespace ohf {
    class RequestBody {
    public:
        RequestBody(const MediaType &contentType, const char *content);

        RequestBody(const MediaType &contentType, const char *content, int offset, int byteCount);

        RequestBody(const MediaType &contentType, const std::string &content);

        RequestBody(const MediaType &contentType, std::istream *stream);

        unsigned int contentLength();

        MediaType contentType();

    private:
        std::string content;
        MediaType mediaType;
    };
}

#endif //OKHTTPFORK_REQUESTBODY_HPP
