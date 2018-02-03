//
// Created by Good_Pudge.
//

#include <sstream>
#include <ohf/FormBody.hpp>
#include <ohf/Exception.hpp>
#include <ohf/HttpURL.hpp>
#include <ohf/RangeException.hpp>

namespace ohf {
    std::string FormBody::encodedName(Uint32 index) const {
        return HttpURL::encode(name(index));
    }

    std::string FormBody::encodedValue(Uint32 index) const {
        return HttpURL::encode(value(index));
    }

    std::string FormBody::name(Uint32 index) const {
        Uint32 i = index * 2;
        if(i >= namesValues.size())
            throw RangeException(i);
        return namesValues[i];
    }

    std::string FormBody::value(Uint32 index) const {
        Uint32 i = index * 2 + 1;
        if (i >= namesValues.size())
            throw RangeException(i);
        return namesValues[i];
    }

    Uint32 FormBody::size() const {
        return (Uint32) namesValues.size() / 2;
    }

    FormBody::FormBody(const Builder *builder) :
            RequestBody("application/x-www-form-urlencoded", std::vector<Int8>()),
            namesValues(builder->namesValues)
    {
        std::stringstream ss;
        for (Uint32 i = 0; i < size(); i++) {
            ss << HttpURL::encode(name(i));
            ss << '=' << HttpURL::encode(value(i));
            ss << '&';
        }

        std::string ready = ss.str();
        ready.erase(ready.length() - 1);
        content.insert(content.end(), ready.begin(), ready.end());
    }
}