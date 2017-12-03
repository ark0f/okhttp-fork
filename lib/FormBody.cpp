//
// Created by Good_Pudge.
//

#include <sstream>
#include <ohf/FormBody.hpp>
#include <ohf/Exception.hpp>
#include <ohf/HttpURL.hpp>

namespace ohf {
    std::string FormBody::encodedName(Uint32 index) const {
        return HttpURL::encode(name(index));
    }

    std::string FormBody::encodedValue(Uint32 index) const {
        return HttpURL::encode(value(index));
    }

    std::string FormBody::name(Uint32 index) const {
        if (index > names.size())
            throw Exception(Exception::Code::OUT_OF_RANGE, "Out of range: " + std::to_string(index));
        return names[index];
    }

    std::string FormBody::value(Uint32 index) const {
        if (index > values.size())
            throw Exception(Exception::Code::OUT_OF_RANGE, "Out of range: " + std::to_string(index));
        return values[index];
    }

    Uint32 FormBody::size() const {
        return names.size();
    }

    FormBody::FormBody(const Builder *builder) :
            RequestBody("application/x-www-form-urlencoded", std::vector<char>()),
            names(builder->names),
            values(builder->values)
    {
        std::stringstream ss;
        for (int i = 0; i < names.size() - 1; i++) {
            std::string name = names[i];
            std::string value = values[i];

            ss << HttpURL::encode(name);
            if(!value.empty()) ss << '=' << HttpURL::encode(value);
            ss << '&';
        }
        ss << HttpURL::encode(names[names.size() - 1]);
        std::string value = values[values.size() - 1];
        if(!value.empty()) ss << '=' << HttpURL::encode(value);

        std::string ready = ss.str();
        content.insert(content.end(), ready.begin(), ready.end());
    }
}