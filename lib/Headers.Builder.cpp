//
// Created by Good_Pudge.
//

#include <ohf/Headers.hpp>
#include <ohf/Exception.hpp>
#include "util/string.hpp"

namespace ohf {
    Headers::Builder &Headers::Builder::add(const std::string &line) {
        std::vector<std::string> nameValue = util::string::split(line, ": ");
        if (nameValue.size() != 2)
            throw Exception(Exception::Code::INVALID_HEADER_LINE, "Invalid header line: " + line);
        this->add(nameValue[0], nameValue[1]);
        return *this;
    }

    Headers::Builder &Headers::Builder::add(const std::string &name, const std::string &value) {
        if (name.empty())
            throw Exception(Exception::Code::HEADER_NAME_IS_EMPTY, "Header is empty: value: " + value);
        namesAndValues.push_back(name);

        if (value.empty())
            throw Exception(Exception::Code::HEADER_VALUE_IS_EMPTY, "Header is empty: name: " + name);
        namesAndValues.push_back(value);

        return *this;
    }

    Headers Headers::Builder::build() const {
        return {this};
    }

    std::string Headers::Builder::get(std::string name) const {
        util::string::toLower(name);
        for (auto it = namesAndValues.begin(); it != namesAndValues.end(); it += 2) {
            std::string element = *it;
            util::string::toLower(element);
            if (name == element)
                return *(++it);

        }
        return std::string();
    }

    Headers::Builder &Headers::Builder::removeAll(std::string name) {
        util::string::toLower(name);
        for (auto it = namesAndValues.begin(); it != namesAndValues.end(); it += 2) {
            std::string element = *it;
            util::string::toLower(element);
            if (name == element) {
                namesAndValues.erase(it);
                namesAndValues.erase(++it);
                it -= 2;
            }
        }

        return *this;
    }

    Headers::Builder &Headers::Builder::set(const std::string &name, const std::string &value) {
        removeAll(name);
        return add(name, value);
    }
}
