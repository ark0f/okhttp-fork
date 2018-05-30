//
// Created by Good_Pudge.
//

#ifndef TESTS_EXCEPTION_CATCH_HPP
#define TESTS_EXCEPTION_CATCH_HPP

#include <ohf/Exception.hpp>
#include <sstream>
#include <catch.hpp>

using namespace ohf;

namespace Catch {
    template<>
    struct StringMaker<Exception> {
        static std::string convert(Exception const& e) {
            return std::to_string((int) e.code());
        }
    };
}

class ExceptionMatcher : public Catch::MatcherBase<ohf::Exception> {
public:
    explicit ExceptionMatcher(Exception::Code code) : mCode(code) {}

    bool match(Exception const &e) const override {
        mMessage = e.message();
        return e.code() == mCode;
    }

    std::string describe() const override {
        std::ostringstream oss;
        oss << "equal " << (int) mCode << " with message: " << mMessage;
        return oss.str();
    }

private:
    Exception::Code mCode;
    mutable std::string mMessage;
};

#define REQUIRE_THROWS_CODE(expr, code) \
    REQUIRE_THROWS_MATCHES(expr, Exception, ExceptionMatcher(code))

#endif // TESTS_EXCEPTION_CATCH_HPP
