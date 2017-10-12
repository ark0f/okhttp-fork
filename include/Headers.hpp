//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_HEADERS_HPP
#define OKHTTPFORK_HEADERS_HPP

#include <vector>
#include <map>

namespace ohf {
    class Headers {
    public:
        class Builder {
        public:
            Builder &add(const std::string &line);

            Builder &add(const std::string &name, const std::string &value);

            Headers build();

            std::string get(std::string name) const;

            Builder &removeAll(std::string name);

            Builder &set(const std::string &name, const std::string &value);

        private:
            // std::map<std::string, std::vector<std::string>> headers;
            std::vector<std::string> namesAndValues;

            friend class ohf::Headers;
        };

        Headers(const std::map<std::string, std::string> &headers);

        std::string get(std::string name) const;

        time_t getDate() const;

        std::string name(int i) const;

        std::vector<std::string> names() const;

        Builder newBuilder() const;

        // static Headers of(...);
        int size() const;

        // std::map<const char *, std::vector<const char *>> toMultimap();
        std::string value(int index) const;

        std::vector<std::string> values(const std::string &name) const;

        std::string toString() const;

        bool operator==(const Headers &headers);

        friend std::ostream &operator<<(std::ostream &stream, const Headers &headers);
    private:
        Headers(const Builder *builder);

        std::vector<std::string> namesAndValues;
    };
}

#endif //OKHTTPFORK_HEADERS_HPP
