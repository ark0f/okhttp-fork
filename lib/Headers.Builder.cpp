//
// Created by Good_Pudge.
//

#include "../include/Headers.hpp"
#include "../util/include/string.hpp"
#include "../include/Exception.hpp"

using namespace ohf;

void Headers::Builder::add(const std::string &line) {
    std::vector<std::string> nameValue = util::string::split(line, ": ");
    if (nameValue.size() != 2)
        throw Exception(Exception::Code::INVALID_HEADER_LINE, "Invalid header line: " + line);
    this->add(nameValue[0], nameValue[1]);
}

void Headers::Builder::add(const std::string &name, const std::string &value) {
    namesAndValues.push_back(name);
    namesAndValues.push_back(value);
}

Headers Headers::Builder::build() {
    Headers f_headers;
    f_headers.namesAndValues = namesAndValues;
    return f_headers;
}

std::string Headers::Builder::get(std::string name) {
    util::string::toLower(name);
    for (auto it = namesAndValues.begin(); it != namesAndValues.end(); it += 2) {
        std::string element = *it;
        util::string::toLower(element);
        if (name == element)
            return *(++it);

    }
    throw Exception(Exception::Code::HEADER_NOT_EXISTS, "Header not exists: " + name);
}

void Headers::Builder::removeAll(std::string name) {
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
}

void Headers::Builder::set(const std::string &name, const std::string &value) {
    removeAll(name);
    namesAndValues.push_back(name);
    namesAndValues.push_back(value);
}
