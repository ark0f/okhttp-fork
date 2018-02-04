//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_REQUESTBODY_HPP
#define OKHTTPFORK_REQUESTBODY_HPP

#include <cstdio>
#include <vector>
#include "Config.hpp"
#include "MediaType.hpp"

namespace ohf {
    class Request;
    class MultipartBody;

    class RequestBody {
    public:
        RequestBody();

        RequestBody(const MediaType &contentType, const char *content, size_t count);

        RequestBody(const MediaType &contentType, const std::string &content);

        RequestBody(const MediaType &contentType, const std::vector<Int8> &content);

        RequestBody(const MediaType &contentType, std::istream &stream);

        Uint64 contentLength();

        MediaType contentType();

    protected:
        std::vector<Int8> content;
        MediaType mediaType;

        friend class ohf::MultipartBody;
        friend class ohf::Request;
    };
}

#endif //OKHTTPFORK_REQUESTBODY_HPP
