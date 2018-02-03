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
                     std::streambuf *buffer = new StreamBuf(1024, 1024));

        ResponseBody(const MediaType &mediaType, const std::vector<Int8> &content,
                     std::streambuf *buffer = new StreamBuf(1024, 1024));

        ResponseBody(const MediaType &mediaType, const std::string &content,
                     std::streambuf *buffer = new StreamBuf(1024, 1024));

        ResponseBody(const MediaType &mediaType, std::istream &stream,
                     std::streambuf *buffer = new StreamBuf(1024, 1024));

        std::vector<Int8> bytes() const;

        std::string string() const;

        std::istream &stream() const;

        Uint64 contentLength() const;

        MediaType contentType() const;

    private:
        std::shared_ptr<std::istream> is;
        std::vector<Int8> content;
        MediaType mediaType;
    };
}

#endif //OKHTTPFORK_RESPONSEBODY_HPP
