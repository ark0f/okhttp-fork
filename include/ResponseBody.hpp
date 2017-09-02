//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_RESPONSEBODY_HPP
#define OKHTTPFORK_RESPONSEBODY_HPP

#include "MediaType.hpp"

namespace ohf {
    class ResponseBody {
    public:
        ResponseBody(const MediaType &mediaType, const char *content);

        ResponseBody(const MediaType &mediaType, const std::string &content);

        char *bytes();

        // std::istream stream();
        // void close();
        unsigned int contentLength();

        MediaType contentType();

        std::string string();

    private:
        std::string content;
        MediaType mediaType;
    };
}

#endif //OKHTTPFORK_RESPONSEBODY_HPP
