//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_STRING_HPP
#define OKHTTPFORK_STRING_HPP

#include <cctype>
#include <string>
#include <vector>
#include <unordered_map>

namespace util {
    namespace string {
        std::vector<std::string> split(std::string s, const std::string &delimiter);

        std::vector<std::string> split(std::string s, const std::vector<std::string> &delimiters);

        inline bool startsWith(const std::string &s, const std::string &prefix) {
            if(s.length() >= prefix.length())
                return s.substr(0, prefix.length()) == prefix;
            return false;
        }

        inline bool endsWith(const std::string &s, const std::string &postfix) {
            if (s.length() >= postfix.length())
                return s.substr(s.length() - postfix.length(), postfix.length()) == postfix;
            return false;
        }

        inline bool contains(const std::string &s, const std::string &data) {
            return s.find(data) != std::string::npos;
        }

        inline void toLower(std::string &s) {
            for (char &i : s) i = std::tolower(i);
        }
    }
}

#endif //OKHTTPFORK_STRING_HPP
