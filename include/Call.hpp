//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_CALL_HPP
#define OKHTTPFORK_CALL_HPP

#include "Response.hpp"
#include "Request.hpp"

namespace ohf {
    class Call {
    public:
        void cancel();

        Response execute();

        bool isCanceled();

        bool isExecuted();

        Request request();
    };
}

#endif //OKHTTPFORK_CALL_HPP
