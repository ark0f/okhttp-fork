//
// Created by Good_Pudge.
//

#include <ohf/FormBody.hpp>
#include <ohf/HttpURL.hpp>

namespace ohf {
    FormBody::Builder& FormBody::Builder::add(const std::string &name, const std::string &value) {
        namesValues.push_back(name);
        namesValues.push_back(value);
        return *this;
    }

    FormBody FormBody::Builder::build() {
        return {this};
    }
}