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
        Call(Request &request) {};

        virtual Response execute() = 0;

        virtual Request request() = 0;

        virtual void cancel() = 0;

        virtual bool isCanceled() = 0;

        virtual bool isExecuted() = 0;
    };
}

#endif //OKHTTPFORK_CALL_HPP
