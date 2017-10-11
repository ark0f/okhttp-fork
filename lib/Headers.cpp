//
// Created by Good_Pudge.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "../include/Headers.hpp"
#include "../include/Exception.hpp"
#include "../util/string.hpp"
#include "../util/util.hpp"

namespace ohf {
    Headers::Headers(const std::map<std::string, std::string> &headers) {
        for (const auto &header : headers) {
            std::string headerName = header.first;
            if (headerName.empty())
                throw Exception(Exception::Code::HEADER_IS_EMPTY, "Header is empty: ");
            namesAndValues.push_back(headerName);

            std::string headerContent = header.second;
            if (headerContent.empty())
                throw Exception(Exception::Code::HEADER_IS_EMPTY, "Header is empty: " + headerName);
            namesAndValues.push_back(header.second);
        }
    }

    std::string Headers::get(std::string name) const {
        util::string::toLower(name);
        for (auto it = namesAndValues.begin(); it != namesAndValues.end(); it += 2) {
            std::string element = *it;
            util::string::toLower(element);
            if (name == element)
                return *(++it);
        }
        return std::string();
    }

    time_t Headers::getDate() const {
        return util::parseDate(this->get("Date"), "%a, %d %b %Y %H:%M:%S GMT");
    }

    std::string Headers::name(int i) const {
        if (i * 2 > namesAndValues.size())
            throw Exception(Exception::Code::OUT_OF_RANGE, "Out of range: " + i);
        return namesAndValues[i * 2];
    }

    std::vector<std::string> Headers::names() const {
        std::vector<std::string> names_;
        for (auto it = namesAndValues.begin(); it != namesAndValues.end(); it += 2) {
            names_.push_back(*it);
        }
        return names_;
    }

    Headers::Builder Headers::newBuilder() const {
        Headers::Builder builder;
        builder.namesAndValues = namesAndValues;
        return builder;
    }

    int Headers::size() const {
        return namesAndValues.size() / 2;
    }

    std::string Headers::value(int index) const {
        if (index * 2 + 1 > namesAndValues.size())
            throw Exception(Exception::Code::OUT_OF_RANGE, "Out of range: " + index);
        return namesAndValues[index];
    }

    std::vector<std::string> Headers::values(const std::string &name) const {
        std::vector<std::string> values;
        auto begin = namesAndValues.begin();
        for (int i = 0; i < namesAndValues.size(); i += 2) {
            if (*begin == name) {
                ++begin;
                values.push_back(*begin);
            }
        }
        return values;
    }

    bool Headers::operator==(const Headers &headers) {
        auto nav1 = headers.namesAndValues;
        std::sort(nav1.begin(), nav1.end());
        auto nav2 = std::move(this->namesAndValues);
        std::sort(nav2.begin(), nav2.end());

        return nav1 == nav2;
    }

    std::ostream &operator<<(std::ostream &stream, const Headers &headers) {
        auto begin = headers.namesAndValues.begin();
        for (int i = 0; i < headers.namesAndValues.size(); i += 2) {
            stream << *begin << ": ";
            ++begin;
            stream << *begin << "\r\n";
            ++begin;
        }
        return stream;
    }

    Headers::Headers(const Builder *builder): namesAndValues(builder->namesAndValues) {}
}
