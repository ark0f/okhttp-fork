//
// Created by Good_Pudge.
//

#include "../include/Headers.hpp"
#include "../util/include/string.hpp"
#include "../include/Exception.hpp"

using namespace ohf;

void Headers::Builder::add(const std::string &line) {
    std::vector<std::string> nameValue = util::string::split(line, ": ");
    if (nameValue.size() > 1) {
        this->add(nameValue[0], nameValue[1]);
        return;
    }
    throw Exception(Exception::Code::INVALID_HEADER_LINE, "Invalid header line: " + line);
}

void Headers::Builder::add(const std::string &name, const std::string &value) {
    headers[name] = value;
}

Headers Headers::Builder::build() {
    return Headers(headers);
}

std::string Headers::Builder::get(const std::string &name) {
    if (headers.count(name) == 1u)
        return headers[name];
    throw Exception(Exception::Code::HEADER_NOT_EXISTS, "Header not exists: " + name);
}

void Headers::Builder::set(const std::string &name, const std::string &value) {
    this->add(name, value);
}

std::string &Headers::Builder::operator[](const std::string &name) {
    if (headers.count(name) == 0u)
        headers[name] = "";
    return headers[name];
}