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
        static const RequestBody EMPTY;

        RequestBody(const MediaType &contentType, const char *content, size_t count);

        RequestBody(const MediaType &contentType, const std::string &content);

        RequestBody(const MediaType &contentType, const std::vector<Int8> &content);

        RequestBody(const MediaType &contentType, std::istream &stream);

        Uint32 contentLength();

        MediaType contentType();

        RequestBody *clone() const;

    private:
        RequestBody();

    protected:
        std::vector<Int8> content;
        MediaType mediaType;

        friend class ohf::MultipartBody;
        friend class ohf::Request;
    };
}

#endif //OKHTTPFORK_REQUESTBODY_HPP
