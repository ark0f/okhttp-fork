//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_MEDIATYPE_HPP
#define OKHTTPFORK_MEDIATYPE_HPP

#include <string>

namespace ohf {
    class MediaType {
    public:
        static const MediaType EMPTY;

        explicit MediaType(const std::string &str);

        MediaType(const char *str);

        std::string boundary() const;

        std::string boundary(const std::string &defaultValue) const;

        std::string charset() const;

        std::string charset(const std::string &defaultValue) const;

        std::string subtype() const;

        std::string type() const;

        bool operator==(const MediaType &mediaType);

        std::string toString() const;

        friend std::ostream &operator<<(std::ostream &stream, const MediaType &mediaType);
    private:
        std::string
                mBoundary,
                mCharset,
                mSubType,
                mType;

        MediaType() = default;
    };
}

#endif //OKHTTPFORK_MEDIATYPE_HPP