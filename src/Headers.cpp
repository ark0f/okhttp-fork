//
// Created by Good_Pudge.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <ohf/Headers.hpp>
#include <ohf/Exception.hpp>
#include <ohf/RangeException.hpp>
#include "util/string.hpp"
#include "util/util.hpp"

namespace ohf {
    Headers::Headers(const std::map<std::string, std::string> &headers) {
        auto begin = headers.begin();
        for (Uint32 i = 0; i < headers.size(); i++) {
            auto header = std::next(begin, i);
            std::string headerName = header->first;
            std::string headerValue = header->second;

            if(headerName.empty() || headerValue.empty()) {
                throw Exception(Exception::Code::HEADER_IS_EMPTY, "Header is empty: name: \"" + headerName
                                                                  + "\" value: \"" + headerValue
                                                                  + "\" index: " + std::to_string(i));
            }

            namesValues.push_back(headerName);
            namesValues.push_back(headerValue);
        }
    }

    const Headers::Iterator Headers::begin() const {
        return {0, this};
    }

    Headers::Iterator Headers::begin() {
        return {0, this};
    }

    const Headers::Iterator Headers::end() const {
        return {this->size(), this};
    }

    Headers::Iterator Headers::end() {
        return {this->size(), this};
    }

    std::string Headers::get(std::string name) const {
        util::string::toLower(name);
        for (auto it = namesValues.begin(); it != namesValues.end(); it += 2) {
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
        Uint32 i = index * 2;
        if (i >= namesValues.size())
            throw RangeException(index);
        return namesValues[i];
    }

    std::vector<std::string> Headers::names() const {
        std::vector<std::string> names;
        for (auto it = namesValues.begin(); it != namesValues.end(); it += 2) {
            if (std::find(names.begin(), names.end(), *it) == names.end())
                names.push_back(*it);
        }
        return names;
    }

    Headers::Builder Headers::newBuilder() const {
        Headers::Builder builder;
        builder.namesValues = namesValues;
        return builder;
    }

    Uint32 Headers::size() const {
        return (Uint32) namesValues.size() / 2;
    }

    std::string Headers::value(Uint32 index) const {
        Uint32 i = index * 2 + 1;
        if (i >= namesValues.size())
            throw RangeException(index);
        return namesValues[i];
    }

    std::vector<std::string> Headers::values(std::string name) const {
        util::string::toLower(name);
        std::vector<std::string> values;
        for (auto it = namesValues.begin(); it != namesValues.end(); it += 2) {
            std::string it_name = *it;
            util::string::toLower(it_name);
            if (it_name == name) values.push_back(*(it + 1));
        }
        return values;
    }

    Headers::Pair Headers::pair(Uint32 index) const {
        return {this->name(index), this->value(index)};
    }

    std::string Headers::toString() const {
        std::stringstream ss;
        auto begin = namesValues.begin();
        for (unsigned int i = 0; i < namesValues.size(); i += 2) {
            ss << *begin << ": ";
            ++begin;
            ss << *begin << "\r\n";
            ++begin;
        }
        return ss.str();
    }

    std::string Headers::operator [](const std::string &name) const {
        return get(name);
    }

    bool Headers::operator ==(const Headers &headers) const {
        auto nav1 = headers.namesValues;
        std::sort(nav1.begin(), nav1.end());
        auto nav2 = this->namesValues;
        std::sort(nav2.begin(), nav2.end());

        return nav1 == nav2;
    }

    std::ostream &operator<<(std::ostream &stream, const Headers &headers) {
        stream << headers.toString();
        return stream;
    }

    Headers::Headers(const Builder *builder) : namesValues(builder->namesValues) {}
}
