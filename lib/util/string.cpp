//
// Created by Good_Pudge.
//

#include <sstream>
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
            std::vector<std::string> all_tokens;
            for(const auto &delimiter : delimiters) {
                std::vector<std::string> tokens = split(s, delimiter);
                all_tokens.insert(all_tokens.end(), tokens.begin(), tokens.end());
            }
            return all_tokens;
        }
    }
}
