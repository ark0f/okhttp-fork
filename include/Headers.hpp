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
            void add(const std::string &line);

            void add(const std::string &name, const std::string &value);

            Headers build();

            std::string get(std::string name);

            void removeAll(std::string name);

            void set(const std::string &name, const std::string &value);

            friend class Headers;

        private:
            // std::map<std::string, std::vector<std::string>> headers;
            std::vector<std::string> namesAndValues;

        };

        Headers() = default;
        Headers(const std::map<std::string, std::string> &headers);

        bool operator==(const Headers &headers); // TODO: Compare values
        std::string get(std::string name);

        time_t getDate();
        std::string name(int i);

        std::vector<std::string> names();

        Builder newBuilder();

        // static Headers of(...);
        int size();

        // std::map<const char *, std::vector<const char *>> toMultimap();
        std::string value(int index);

        std::vector<std::string> values(const std::string &name);

    private:
        std::vector<std::string> namesAndValues;
    };
}

#endif //OKHTTPFORK_HEADERS_HPP
