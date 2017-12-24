//
// Created by Good_Pudge.
//

#include <ohf/FormBody.hpp>
#include <ohf/HttpURL.hpp>

namespace ohf {
    FormBody::Builder& FormBody::Builder::add(const std::string &name, const std::string &value) {
        names.push_back(HttpURL::decode(name));
        values.push_back(HttpURL::decode(value));
        return *this;
    }

    FormBody FormBody::Builder::build() {
        return {this};
    }
}