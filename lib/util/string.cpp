//
// Created by Good_Pudge.
//

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
    }
}
