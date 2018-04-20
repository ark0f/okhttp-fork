//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_INTERCEPTOR_HPP
#define OKHTTPFORK_INTERCEPTOR_HPP

#include "TimeUnit.hpp"
#include "Call.hpp"
#include "Connection.hpp"

namespace ohf {
    class Interceptor {
        class Chain {
        public:
            Call* call();

            Connection connection();

            TimeUnit connectTimeout();


        };
    };
}

#endif //OKHTTPFORK_INTERCEPTOR_HPP
