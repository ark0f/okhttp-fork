//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_HEADERS_HPP
#define OKHTTPFORK_HEADERS_HPP

#include "Config.hpp"
#include "TimeUnit.hpp"
#include <vector>
#include <map>

namespace ohf {
    class Headers {
    public:
        typedef std::pair<std::string, std::string> Pair;

        class Iterator {
        public:
            Iterator(Uint32 index, const Headers *headers);

            bool isOutOfRange() const;

            const Pair& operator *() const;

            const Pair& operator *();

            const Pair* operator ->() const;

            const Pair* operator ->();

            const Iterator operator ++(Int32) const;

            const Iterator& operator ++();

            const Iterator operator --(Int32) const;

            const Iterator& operator --();

            const Iterator operator +(Uint32 index) const;

            const Iterator operator -(Uint32 index) const;

            const Iterator& operator +=(Uint32 index);

            const Iterator& operator -=(Uint32 index);

            bool operator ==(const Iterator &right) const;

            bool operator !=(const Iterator &right) const;

        private:
            void swapPair();

            mutable bool outOfRange;
            Pair type;
            Uint32 index;
            const Headers *headers;
        };

        const Iterator begin() const;
        Iterator begin();

        const Iterator end() const;
        Iterator end();

        class Builder {
        public:
            Builder &add(std::string line);

            Builder &add(const std::string &name, const std::string &value);

            Headers build() const;

            std::string get(std::string name) const;

            Builder &removeAll(std::string name);

            Builder &set(const std::string &name, const std::string &value);

        private:
            std::vector<std::string> namesValues;

            friend class ohf::Headers;
        };

        explicit Headers(const std::map<std::string, std::string> &headers);

        std::string get(std::string name) const;

        TimeUnit getDate() const;

        std::string name(Uint32 index) const;

        std::vector<std::string> names() const;

        Builder newBuilder() const;

        // static Headers of(...);
        Uint32 size() const;

        std::string value(Uint32 index) const;

        std::vector<std::string> values(std::string name) const;

        Pair pair(Uint32 index) const;

        std::string toString() const;

        std::string operator [](const std::string &name) const;

        bool operator ==(const Headers &headers) const;

        friend std::ostream &operator<<(std::ostream &stream, const Headers &headers);

    private:
        Headers(const Builder *builder);

        std::vector<std::string> namesValues;
    };
}

#endif //OKHTTPFORK_HEADERS_HPP
