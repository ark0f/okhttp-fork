//
// Created by Good_Pudge.
//

#ifndef TESTS_TIME_UNIT_MATCHER_HPP
#define TESTS_IME_UNIT_MATCHER_HPP

#include <ohf/TimeUnit.hpp>
#include <catch.hpp>
#include <sstream>

class TimeUnitMatcher : public Catch::MatcherBase<ohf::TimeUnit> {
public:
    explicit TimeUnitMatcher(const ohf::TimeUnit &unit) : unit(unit), left(ohf::TimeUnit::ZERO) {};

    bool match(ohf::TimeUnit const &t) const override {
        left = t;
        return unit == t;
    }

    std::string describe() const override {
        std::ostringstream oss;
        oss << "is equal " << left.milliseconds() << "ms and " << unit.milliseconds() << "ms";
        return oss.str();
    }

private:
    ohf::TimeUnit unit;
    mutable ohf::TimeUnit left;
};

#define TIMEUNIT_EQUAL(left, right) \
    CHECK_THAT(left, TimeUnitMatcher(right))

#endif //TESTS_TIME_UNIT_MATCHER_HPP
