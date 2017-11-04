//
// Created by Good_Pudge.
//

#include "../include/FormBody.hpp"
#include "../include/HttpURL.hpp"

namespace ohf {
    FormBody::Builder& FormBody::Builder::add(const std::string &name, const std::string &value) {
        names.push_back(HttpURL::decode(name));
        values.push_back(HttpURL::decode(value));
        return *this;
    }

    FormBody::Builder& FormBody::Builder::add(const std::string &name) {
        names.push_back(HttpURL::decode(name));
        values.emplace_back();
        return *this;
    }

    FormBody FormBody::Builder::build() {
        return {this};
    }
}