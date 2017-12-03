//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_MULTIPARTBODY_HPP
#define OKHTTPFORK_MULTIPARTBODY_HPP

#include "MediaType.hpp"
#include "RequestBody.hpp"
#include "Headers.hpp"

namespace ohf {
    class MultipartBody : public RequestBody {
    public:
        static MediaType MIXED;
        static MediaType ALTERNATIVE;
        static MediaType DIGEST;
        static MediaType PARALLEL;
        static MediaType FORM;

        class Part {
        public:
            Part(const std::string &name, const std::string &value);

            Part(const std::string &name, const std::string &filename, const RequestBody &body);

            Part(const Headers &headers, const RequestBody &body);

            explicit Part(const RequestBody &body);

            RequestBody body() const;

            Headers headers() const;

        private:
            RequestBody mBody;
            Headers mHeaders;

            friend class ohf::MultipartBody;
        };

        class Builder {
        public:
            Builder();

            explicit Builder(const std::string &boundary);

            Builder &addFormDataPart(const std::string &name, const std::string &value);

            Builder &addFormDataPart(const std::string &name, const std::string &filename, const RequestBody &body);

            Builder &addPart(const Headers &headers, const RequestBody &body);

            Builder &addPart(const Part &part);

            Builder &addPart(const RequestBody &body);

            Builder &setType(const MediaType &type);

            MultipartBody build();

        private:
            std::string mBoundary;
            MediaType mType;
            std::vector<Part> mParts;

            friend class ohf::MultipartBody;
        };

        std::string boundary();

        Part part(int index);

        std::vector<Part> parts();

        int size();

        MediaType type();

    private:
        MultipartBody(const Builder *builder);

        std::string mBoundary;
        MediaType mType;
        std::vector<Part> mParts;
    };
}

#endif //OKHTTPFORK_MULTIPARTBODY_HPP
