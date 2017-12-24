//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_CALLBACK_HPP
#define OKHTTPFORK_CALLBACK_HPP

#include "Exception.hpp"
#include "Response.hpp"

namespace ohf {
    class Call;

    class Callback {
    public:
        virtual void onFailure(const Call &call, const Exception &e) = 0;
        virtual void onResponse(const Call &call, const Response &response) = 0;
    };
}

#endif //OKHTTPFORK_CALLBACK_HPP
