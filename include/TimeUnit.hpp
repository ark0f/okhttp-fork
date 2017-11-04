//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_TIMEUNIT_HPP
#define OKHTTPFORK_TIMEUNIT_HPP

#include <ctime>
#include "Config.hpp"

namespace ohf {
    class TimeUnit {
    public:
        enum class Type {
            SECONDS = 1,
            MILLISECONDS = 1000,
            MICROSECONDS = 1000000
        };

        static const TimeUnit ZERO;
        static const TimeUnit MINUS_ONE_SECOND;

        static TimeUnit seconds(float time);
        static TimeUnit milliseconds(Int32 time);
        static TimeUnit microseconds(Int64 time);

        TimeUnit(Int64 count, const TimeUnit::Type &type);

        std::time_t std_time() const;

        float seconds() const;
        Int32 milliseconds() const;
        Int64 microseconds() const;

        // for timeval
        long sec() const;
        long usec() const;

        bool operator ==(const TimeUnit &right) const;
        bool operator !=(const TimeUnit &right) const;
        bool operator >=(const TimeUnit &right) const;
        bool operator <=(const TimeUnit &right) const;
        bool operator >(const TimeUnit &right) const;
        bool operator <(const TimeUnit &right) const;

        TimeUnit operator +(const TimeUnit &right) const;
        TimeUnit operator -(const TimeUnit &right) const;
        TimeUnit operator *(const TimeUnit &right) const;
        TimeUnit operator /(const TimeUnit &right) const;
        TimeUnit operator ^(const TimeUnit &right) const;
    private:
        std::time_t time; // 2036
        long long mMicroseconds;
        long mSec;
        long mUSec;
    };
}

#endif //OKHTTPFORK_TIMEUNIT_HPP
