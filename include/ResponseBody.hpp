//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_RESPONSEBODY_HPP
#define OKHTTPFORK_RESPONSEBODY_HPP

#include <sstream>
#include <vector>
#include <streambuf>
#include <memory>
#include "MediaType.hpp"
#include "Config.hpp"

namespace ohf {
    class ResponseBody {
    public:
        ResponseBody(const MediaType &mediaType, const char *content, size_t count);

        ResponseBody(const MediaType &mediaType, const std::vector<Int8> &content);

        ResponseBody(const MediaType &mediaType, const std::string &content);

        ResponseBody(const MediaType &mediaType, std::istream &stream);

        std::vector<Int8> bytes();

        std::istream &stream();

        unsigned int contentLength();

        MediaType contentType();

        std::string string();

    private:
        std::stringstream ss;
        std::vector<Int8> mContent;
        MediaType mediaType;
    };
}

#endif //OKHTTPFORK_RESPONSEBODY_HPP
