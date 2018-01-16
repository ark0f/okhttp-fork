//
// Created by Good_Pudge.
//

#include <ohf/Headers.hpp>
#include <ohf/Exception.hpp>
#include "util/string.hpp"

namespace ohf {
    Headers::Builder &Headers::Builder::add(std::string line) {
        Uint64 offset = line.find(": ");

        std::string name = line.substr(0, offset);
        line.erase(0, offset + 2);

        std::string value = line.substr(0, line.length());
        
        this->add(name, value);
        return *this;
    }

    Headers::Builder &Headers::Builder::add(const std::string &name, const std::string &value) {
        if (name.empty() || value.empty()) {
            throw Exception(Exception::Code::HEADER_NAME_IS_EMPTY, "Header is empty: name: \"" + name
                                                                   + "\" value: \"" + value + "\"");
        }

        namesAndValues.push_back(name);
        namesAndValues.push_back(value);

        return *this;
    }

    Headers Headers::Builder::build() const {
        return {this};
    }

    std::string Headers::Builder::get(std::string name) const {
        util::string::toLower(name);
        for (auto it = namesAndValues.begin(); it != namesAndValues.end(); it += 2) {
            std::string element = *it;
            util::string::toLower(element);
            if (name == element) return *(++it);
        }
        return std::string();
    }

    Headers::Builder &Headers::Builder::removeAll(std::string name) {
        util::string::toLower(name);
        std::vector<std::string> nav;
        for (auto it = namesAndValues.begin(); it != namesAndValues.end(); it += 2) {
            std::string element = *it;
            util::string::toLower(element);
            if(name != element) {
                nav.insert(nav.end(), it, it + 1);
                nav.insert(nav.end(), it + 1, it + 2);
            }
        }
        namesAndValues.swap(nav);

        return *this;
    }

    Headers::Builder &Headers::Builder::set(const std::string &name, const std::string &value) {
        removeAll(name);
        return add(name, value);
    }
}
