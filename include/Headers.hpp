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

            std::string get(const std::string &name);

            // void removeAll(const char *name);
            void set(const std::string &name, const std::string &value);

            std::string &operator[](const std::string &name);

        private:
            std::map<std::string, std::string> headers;

            friend class Headers;
        };

        bool operator==(const Headers &headers); // TODO: Compare values
        std::string get(const std::string &name);

        std::string &operator[](const std::string &name);

        time_t getDate(); // TODO: Check working capacity
        std::string name(int i);

        std::vector<std::string> names();

        Builder newBuilder();

        static Headers of(const std::map<std::string, std::string> &headers);

        // typedef Headers of(...);
        int size();

        // std::map<const char *, std::vector<const char *>> toMultimap();
        std::string value(int index);

        std::vector<std::string> values();

    private:
        std::map<std::string, std::string> headers;
    };
}

#endif //OKHTTPFORK_HEADERS_HPP
