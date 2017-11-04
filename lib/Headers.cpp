//
// Created by Good_Pudge.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "../include/Headers.hpp"
#include "../include/Exception.hpp"
#include "../lib/util/string.hpp"
#include "../lib/util/util.hpp"

namespace ohf {
    Headers::Headers(const std::map<std::string, std::string> &headers) {
        auto begin = headers.begin();
        for (unsigned int i = 0; i < headers.size(); i++) {
            auto header = std::next(begin, i);
            std::string headerName = header->first;
            if (headerName.empty())
                throw Exception(Exception::Code::HEADER_NAME_IS_EMPTY, "Header is empty: index: " + std::to_string(i));
            namesAndValues.push_back(headerName);

            std::string headerContent = header->second;
            if (headerContent.empty())
                throw Exception(Exception::Code::HEADER_VALUE_IS_EMPTY, "Header is empty: name: " + headerName);
            namesAndValues.push_back(header->second);
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

    TimeUnit Headers::getDate() const {
        return TimeUnit::seconds(util::parseDate(this->get("Date"), "%a, %d %b %Y %H:%M:%S GMT"));
    }

    std::string Headers::name(Uint32 index) const {
        if (index * 2 > namesAndValues.size())
            throw Exception(Exception::Code::OUT_OF_RANGE, "Out of range: " + std::to_string(index));
        return namesAndValues[index * 2];
    }

    std::vector<std::string> Headers::names() const {
        std::vector<std::string> names;
        for (auto it = namesAndValues.begin(); it != namesAndValues.end(); it += 2)
            if(std::find(names.begin(), names.end(), *it) == names.end())
                names.push_back(*it);
        return names;
    }

    Headers::Builder Headers::newBuilder() const {
        Headers::Builder builder;
        builder.namesAndValues = namesAndValues;
        return builder;
    }

    Uint32 Headers::size() const {
        return namesAndValues.size() / 2;
    }

    std::string Headers::value(Uint32 index) const {
        if (index * 2 + 1 > namesAndValues.size())
            throw Exception(Exception::Code::OUT_OF_RANGE, "Out of range: " + std::to_string(index));
        return namesAndValues[index];
    }

    std::vector<std::string> Headers::values(const std::string &name) const {
        std::vector<std::string> values;
        for (auto it = namesAndValues.begin(); it != namesAndValues.end(); it += 2) {
            if (*it == name) values.push_back(*(it + 1));
        }
        return values;
    }

    std::string Headers::toString() const {
        std::stringstream ss;
        auto begin = namesAndValues.begin();
        for (int i = 0; i < namesAndValues.size(); i += 2) {
            ss << *begin << ": ";
            ++begin;
            ss << *begin << "\r\n";
            ++begin;
        }
        return ss.str();
    }

    bool Headers::operator==(const Headers &headers) const {
        auto nav1 = std::move(headers.namesAndValues);
        std::sort(nav1.begin(), nav1.end());
        auto nav2 = std::move(this->namesAndValues);
        std::sort(nav2.begin(), nav2.end());

        return nav1 == nav2;
    }

    std::ostream &operator<<(std::ostream &stream, const Headers &headers) {
        stream << headers.toString();
        return stream;
    }

    Headers::Headers(const Builder *builder): namesAndValues(builder->namesAndValues) {}
}
