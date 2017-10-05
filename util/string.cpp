//
// Created by Good_Pudge.
//

#include <sstream>
#include <algorithm>
#include <iostream>
#include "string.hpp"

using namespace util;

std::vector<std::string> string::split(std::string str, const std::string &delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        std::string token = str.substr(0, pos);
        if (!token.empty())
            tokens.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    if (!str.empty())
        tokens.push_back(str);
    return tokens;
}

bool string::startsWith(std::string s, const std::string &prefix) {
    return s.substr(0, prefix.length()) == prefix;
}

bool string::endsWith(std::string s, const std::string &postfix) {
    if (s.length() >= postfix.length())
        return s.substr(s.length() - postfix.length(), postfix.length()) == postfix;
    return false;
}

bool string::contains(const std::string &s, const std::string &data) {
    return s.find(data) != std::string::npos;
}

void string::toLower(std::string &s) {
    for (char &i : s)
        i = tolower(i);
}

std::string::size_type string::firstIndexOf(const std::string &str, const std::string &find) {
    return str.find(find);
}
