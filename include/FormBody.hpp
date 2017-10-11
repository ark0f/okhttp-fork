//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_FORMBODY_HPP
#define OKHTTPFORK_FORMBODY_HPP

#include "RequestBody.hpp"

namespace ohf {
    class FormBody : public RequestBody {
    public:
        class Builder {
        public:
            Builder &add(const std::string &name, const std::string &value);

            FormBody build();

        private:
            std::vector<std::string> names;
            std::vector<std::string> values;

            friend class ohf::FormBody;
        };

        std::string encodedName(int index) const;

        std::string encodedValue(int index) const;

        std::string name(int index) const;

        std::string value(int index) const;

        int size() const;

    private:
        FormBody(const Builder *builder);

        std::vector<std::string> names;
        std::vector<std::string> values;
    };
}

#endif //OKHTTPFORK_FORMBODY_HPP
