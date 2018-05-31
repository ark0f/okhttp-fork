//
// Created by Good_Pudge.
//

#ifndef TESTS_TIMEUNIT_CATCH_HPP
#define TESTS_TIMEUNIT_CATCH_HPP

#include <ohf/TimeUnit.hpp>
#include <catch.hpp>
#include <sstream>
#include "../../Catch2/include/internal/catch_matchers.h"
#include "../../Catch2/include/catch.hpp"

using namespace ohf;

namespace Catch {
    template<>
    struct StringMaker<TimeUnit> {
        static std::string convert(TimeUnit const& tu) {
            std::string str;
            switch(tu.type()) {
                case TimeUnit::Type::SECONDS: {
                    float integer;
                    float fraction = std::modf(tu.floatValue(), &integer);
                    if(fraction == 0) {
                        str += std::to_string((ohf::Int64) integer);
                    } else {
                        str += std::to_string(integer + fraction);
                    }
                    str += " seconds";
                    break;
                }
                case TimeUnit::Type::MILLISECONDS: {
                    str += std::to_string(tu.value())
                        + " milliseconds";
                    break;
                }
                case TimeUnit::Type::MICROSECONDS: {
                    str += std::to_string(tu.value())
                        + " microseconds";
                    break;
                }
            }
            return str;
        }
    };
}

class TimeUnitMatcher : public Catch::MatcherBase<ohf::TimeUnit> {
public:
    explicit TimeUnitMatcher(const TimeUnit &unit) : mUnit(unit) {};

    bool match(TimeUnit const &e) const override {
        return e.std_time()        == mUnit.std_time()
               && e.seconds()      == mUnit.seconds()
               && e.milliseconds() == mUnit.milliseconds()
               && e.microseconds() == mUnit.microseconds()
               && e.sec()          == mUnit.sec()
               && e.usec()         == mUnit.usec()
               && e.type()         == mUnit.type()
               && e.value()        == mUnit.value()
               && e.floatValue()   == mUnit.floatValue()
               && e                == mUnit;
    }

    std::string describe() const override {
        std::ostringstream oss;
        oss << "equal " << Catch::StringMaker<TimeUnit>::convert(mUnit);
        return oss.str();
    }

private:
    TimeUnit mUnit;
};

#endif // TESTS_TIMEUNIT_CATCH_HPP
