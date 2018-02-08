//
// Created by Good_Pudge.
//

#ifndef TESTS_EXCEPTION_MATCHER_HPP
#define TESTS_EXCEPTION_MATCHER_HPP

#include <ohf/Exception.hpp>
#include <sstream>
#include "catch.hpp"

class ExceptionMatcher : public Catch::MatcherBase<ohf::Exception> {
public:
    explicit ExceptionMatcher(ohf::Exception::Code code) : code(code) {}

    bool match(ohf::Exception const &e) const override {
        codeLeft = e.code();
        message = e.message();
        return e.code() == code;
    }

    std::string describe() const override {
        std::ostringstream oss;
        oss << "equal " << (int) codeLeft << " and " << (int) code << " with message: " << message;
        return oss.str();
    }

private:
    ohf::Exception::Code code;
    mutable ohf::Exception::Code codeLeft;
    mutable std::string message;
};

#define REQUIRE_THROWS_CODE(expr, code) \
    REQUIRE_THROWS_MATCHES(expr, ohf::Exception, ExceptionMatcher(code))

#endif //TESTS_EXCEPTION_MATCHER_HPP
