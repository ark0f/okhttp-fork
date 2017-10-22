//
// Created by Good_Pudge.
//

#include <sstream>
#include "../include/FormBody.hpp"
#include "../include/Exception.hpp"
#include "../include/HttpURL.hpp"

namespace ohf {
    std::string FormBody::encodedName(int index) const {
        return HttpURL::encode(name(index));
    }

    std::string FormBody::encodedValue(int index) const {
        return HttpURL::encode(value(index));
    }

    std::string FormBody::name(int index) const {
        if (index > names.size())
            throw Exception(Exception::Code::OUT_OF_RANGE, "Out of range:" + std::to_string(index));
        return names[index];
    }

    std::string FormBody::value(int index) const {
        if (index > values.size())
            throw Exception(Exception::Code::OUT_OF_RANGE, "Out of range:" + std::to_string(index));
        return values[index];
    }

    int FormBody::size() const {
        return names.size();
    }

    FormBody::FormBody(const Builder *builder) :
            RequestBody("application/x-www-form-urlencoded", std::vector<char>()),
            names(builder->names),
            values(builder->values) {
        std::stringstream ss;
        for (int i = 0; i < names.size() - 1; i++) {
            std::string name = names[i];
            std::string value = values[i];

            ss << HttpURL::encode(name) << '=' << HttpURL::encode(value) << '&';
        }
        ss << HttpURL::encode(names[names.size() - 1])
           << '='
           << HttpURL::encode(values[values.size() - 1]);
        std::string ready = ss.str();
        content.insert(content.end(), ready.begin(), ready.end());
    }
}