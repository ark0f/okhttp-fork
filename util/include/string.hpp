//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_STRING_HPP
#define OKHTTPFORK_STRING_HPP

#include <vector>

namespace util {
    namespace string {
        std::vector<std::string> split(std::string s, const std::string &delimiter);

        bool startsWith(std::string s, const std::string &prefix);

        bool endsWith(std::string s, const std::string &postfix);

        bool contains(const std::string &s, const std::string &data);

        void toLower(std::string &s); // TODO: Unicode support
        std::string::size_type first_index_of(const std::string &str, const std::string &find);

        int containsCount(std::string s, const std::string &what);
    }
}

#endif //OKHTTPFORK_STRING_HPP
