//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_STRING_HPP
#define OKHTTPFORK_STRING_HPP

#include <vector>

namespace util {
    namespace string {
        std::vector<std::string> split(std::string s, const std::string &delimiter);

        inline bool startsWith(std::string s, const std::string &prefix) {
            return s.substr(0, prefix.length()) == prefix;
        }

        inline bool endsWith(std::string s, const std::string &postfix) {
            if (s.length() >= postfix.length())
                return s.substr(s.length() - postfix.length(), postfix.length()) == postfix;
            return false;
        }

        inline bool contains(const std::string &s, const std::string &data) {
            return s.find(data) != std::string::npos;
        }

        inline void toLower(std::string &s) {
            for (char &i : s) i = tolower(i);
        }

        inline std::string::size_type firstIndexOf(const std::string &str, const std::string &find) {
            return str.find(find);
        }
    }
}

#endif //OKHTTPFORK_STRING_HPP
