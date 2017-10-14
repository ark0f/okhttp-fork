//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_CALL_HPP
#define OKHTTPFORK_CALL_HPP

#include "Response.hpp"
#include "Request.hpp"
#include "Callback.hpp"
#include <memory>

namespace ohf {
    class Call {
    public:
        class Factory {
        public:
            virtual std::unique_ptr<Call> newCall(const Request &request) = 0;
        };

        virtual void enqueue(const Callback &callback) = 0;

        virtual void enqueue(void(*onResponse)(const Call &, const Response &),
                             void(*onFailure)(const Call&, const Exception &)) = 0;

        virtual Response execute() = 0;

        virtual Request request() = 0;

        virtual void cancel() = 0;

        virtual bool isCanceled() = 0;

        virtual bool isExecuted() = 0;
    };
}

#endif //OKHTTPFORK_CALL_HPP
