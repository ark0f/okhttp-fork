//
// Created by Good_Pudge.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include "../include/Headers.hpp"
#include "../util/include/string.hpp"
#include "../include/Exception.hpp"

using namespace ohf;

//-----------Headers::Builder-----------
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
    Headers ohfHeaders;
    ohfHeaders.headers = headers;
    return ohfHeaders;
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

//-----------Headers-----------
bool Headers::operator==(const Headers &headers) {
    return this == &headers;
}

std::string Headers::get(const std::string &name) {
    if (headers.count(name) == 1u)
        return headers[name];
    throw Exception(Exception::Code::HEADER_NOT_EXISTS, "Header not exists: " + name);
}

std::string &Headers::operator[](const std::string &name) {
    return headers[name];
}

time_t Headers::getDate() {
    time_t time = -1;
    if (headers.count("Date") == 1u) {
        std::tm t{};
        std::string date = headers["Date"];
        std::istringstream iss(date);
        iss >> std::get_time(&t, "%a, %d %b %Y %H:%M:%S GMT");
        time = std::mktime(&t);
    }
    return time;
}

std::string Headers::name(int i) {
    return std::next(headers.begin(), i)->first;
}

std::vector<std::string> Headers::names() {
    std::vector<std::string> names_;
    for (auto i = headers.begin(); i != headers.end(); i++) {
        names_.push_back(i->first);
    }
    return names_;
}

Headers::Builder Headers::newBuilder() {
    Headers::Builder builder;
    builder.headers = headers;
    return builder;
}

Headers Headers::of(const std::map<std::string, std::string> &headers) {
    Headers ohfHeaders;
    ohfHeaders.headers = headers;
    return ohfHeaders;
}

int Headers::size() {
    return headers.size();
}

std::string Headers::value(int index) {
    return std::next(headers.begin(), index)->second;
}

std::vector<std::string> Headers::values() {
    std::vector<std::string> values_;
    for (auto i = headers.begin(); i != headers.end(); i++) {
        values_.push_back(i->second);
    }
    return values_;
}
