//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_RESPONSEBODY_HPP
#define OKHTTPFORK_RESPONSEBODY_HPP

#include <vector>
#include <streambuf>
#include <memory>
#include <ohf/MediaType.hpp>
#include <ohf/IOStreamBuf.hpp>

namespace ohf {
    class ResponseBody {
    public:
        class StreamBuf : public IOStreamBuf {
        public:
            StreamBuf(Int32 write, Int32 read);

            void vector(const std::vector<Int8> &vector);

        protected:
            Int32 write(const char *data, Int32 length) override;

            Int32 read(char *data, Int32 length) override;

        private:
            std::vector<Int8> mVector;
        };

        ResponseBody(const MediaType &mediaType, const char *content, size_t count,
                     StreamBuf *buffer = new StreamBuf(1024, 1024));

        ResponseBody(const MediaType &mediaType, const std::vector<Int8> &content,
                     StreamBuf *buffer = new StreamBuf(1024, 1024));

        ResponseBody(const MediaType &mediaType, const std::string &content,
                     StreamBuf *buffer = new StreamBuf(1024, 1024));

        ResponseBody(const MediaType &mediaType, std::istream &stream,
                     StreamBuf *buffer = new StreamBuf(1024, 1024));

        std::vector<Int8> bytes();

        std::string string();

        std::istream &stream();

        Uint64 contentLength();

        MediaType contentType();

    private:
        std::shared_ptr<std::istream> is;
        std::vector<Int8> content;
        MediaType mediaType;
    };
}

#endif //OKHTTPFORK_RESPONSEBODY_HPP
