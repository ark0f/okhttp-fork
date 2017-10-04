//
// Created by Good_Pudge.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include "../include/Headers.hpp"
#include "../include/Exception.hpp"
#include "../util/string.hpp"
#include "../util/util.hpp"

using namespace ohf;

Headers::Headers(const std::map<std::string, std::string> &headers) {
    for (const auto &header : headers) {
        namesAndValues.push_back(header.first);
        namesAndValues.push_back(header.second);
    }
}

bool Headers::operator==(const Headers &headers) {
    return this == &headers;
}

std::string Headers::get(std::string name) const {
    util::string::toLower(name);
    for (auto it = namesAndValues.begin(); it != namesAndValues.end(); it += 2) {
        std::string element = *it;
        util::string::toLower(element);
        if (name == element)
            return *(++it);

    }
    throw Exception(Exception::Code::HEADER_NOT_EXISTS, "Header not exists: " + name);
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
        auto it = std::next(begin, i);
        if (*it == name) values.push_back(*++it);
    }
    return values;
}
