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

            while(true) {
                auto offset = std::string::npos;
                std::string::size_type delim_size = 0;
                for (const auto &delimiter : delimiters) {
                    auto current_offset = s.find(delimiter);
                    if (current_offset < offset) {
                        offset = current_offset;
                        delim_size = delimiter.length();
                    }
                }

                if(offset == std::string::npos) {
                    break;
                }

                std::string token(s, 0, offset);
                if(!token.empty()) tokens.push_back(token);

                s.erase(0, offset + delim_size);
            }

            if(!s.empty()) tokens.push_back(s);

            return tokens;
        }
    }
}
