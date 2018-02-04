//
// Created by Good_Pudge.
//

#include <sstream>
#include <tuple>
#include "string.hpp"

namespace util {
    namespace string {
        std::vector<std::string> split(std::string str, const std::string &delimiter) {
            std::vector<std::string> tokens;
            size_t pos = 0;
            while ((pos = str.find(delimiter)) != std::string::npos) {
                std::string token = str.substr(0, pos);
                if (!token.empty()) tokens.push_back(token);
                str.erase(0, pos + delimiter.length());
            }
            if (!str.empty()) tokens.push_back(str);
            return tokens;
        }

        std::vector<std::string> split(std::string s, const std::vector<std::string> &delimiters) {
            std::vector<std::string> tokens;

            while(!s.empty()) {
                auto min_offset = std::string::npos;
                std::string::size_type current_offset;
                for (const auto &delimiter : delimiters) {
                    current_offset = s.find(delimiter);
                    if (current_offset < min_offset) min_offset = current_offset;
                }
                tokens.emplace_back(s, s.length() - min_offset);
                s.erase(0, min_offset);
            }

            return tokens;
        }
    }
}
