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
            std::vector<std::string> names, values;

            friend class ohf::FormBody;
        };

        std::string encodedName(Uint32 index) const;

        std::string encodedValue(Uint32 index) const;

        std::string name(Uint32 index) const;

        std::string value(Uint32 index) const;

        Uint32 size() const;

    private:
        FormBody(const Builder *builder);

        std::vector<std::string> names, values;
    };
}

#endif //OKHTTPFORK_FORMBODY_HPP
