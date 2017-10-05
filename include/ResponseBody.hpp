//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_RESPONSEBODY_HPP
#define OKHTTPFORK_RESPONSEBODY_HPP

#include <vector>
#include <streambuf>
#include <memory>
#include "MediaType.hpp"

namespace ohf {
    class ResponseBody {
    public:
        ResponseBody(const MediaType &mediaType, const char *content, size_t count);

        ResponseBody(const MediaType &mediaType, const std::vector<char> &content);

        ResponseBody(const MediaType &mediaType, const std::string &content);

        ResponseBody(const MediaType &mediaType, std::istream &stream);

        std::vector<char> bytes();

        std::istream &stream();

        unsigned int contentLength();

        MediaType contentType();

        std::string string();

    private:
        class StreamBuf : public std::streambuf {
        public:
            StreamBuf(ResponseBody *body) :
                    cur(traits_type::eof()),
                    body(body),
                    offset(0) {};
        protected:
            int uflow() override {
                int c = underflow();
                cur = traits_type::eof();
                return c;
            }

            int underflow() override {
                if (cur != traits_type::eof())
                    return cur;

                std::vector<char> bytes = body->bytes();
                if (offset >= bytes.size())
                    return traits_type::eof();
                cur = bytes[offset];
                ++offset;
                return cur;
            }

        private:
            ResponseBody *body;
            int cur;
            unsigned int offset;
        };

        std::shared_ptr<std::istream> is;
        std::vector<char> content;
        MediaType mediaType;
    };
}

#endif //OKHTTPFORK_RESPONSEBODY_HPP
