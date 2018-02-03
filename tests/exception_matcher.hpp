//
// Created by Good_Pudge.
//

#ifndef TESTS_EXCEPTION_MATCHER_HPP
#define TESTS_EXCEPTION_MATCHER_HPP

#include <ohf/Exception.hpp>
#include <sstream>
#include "catch.hpp"

template <class E>
class ExceptionMatcher : public Catch::MatcherBase<E> {
public:
    explicit ExceptionMatcher(ohf::Exception::Code code) : code(code) {}

    bool match(E const &e) const override {
        return e.code() == code;
    }

    std::string describe() const override {
        std::ostringstream oss;
        oss << "is " << (int) code;
        return oss.str();
    }

private:
    ohf::Exception::Code code;
};

#define REQUIRE_THROWS_CODE_AS(expr, exceptionType, code) \
    REQUIRE_THROWS_MATCHES(expr, exceptionType, ExceptionMatcher<exceptionType>(code))

#define REQUIRE_THROWS_CODE(expr, code) REQUIRE_THROWS_CODE_AS(expr, ohf::Exception, code)

#endif //TESTS_EXCEPTION_MATCHER_HPP
