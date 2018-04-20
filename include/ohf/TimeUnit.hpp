//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_TIMEUNIT_HPP
#define OKHTTPFORK_TIMEUNIT_HPP

#include <string>
#include <ctime>
#include "Config.hpp"

namespace ohf {
    class TimeUnit {
    public:
        enum class Type {
            SECONDS,
            MILLISECONDS,
            MICROSECONDS
        };

        static const TimeUnit ZERO;
        static const TimeUnit MINUS_ONE_SECOND;

        static TimeUnit seconds(float time);
        static TimeUnit milliseconds(Int32 time);
        static TimeUnit microseconds(Int64 time);

        TimeUnit(Int64 count, Type type);

        std::time_t std_time() const;

        float seconds() const;
        Int32 milliseconds() const;
        Int64 microseconds() const;

        // timeval
        long sec() const;
        long usec() const;

        // automatic conversion
        Type type() const;
        Int64 value() const;
        float floatValue() const;

        // bool
        bool operator ==(const TimeUnit &right) const;
        bool operator !=(const TimeUnit &right) const;
        bool operator >=(const TimeUnit &right) const;
        bool operator <=(const TimeUnit &right) const;
        bool operator >(const TimeUnit &right) const;
        bool operator <(const TimeUnit &right) const;

        // math
        TimeUnit operator +(const TimeUnit &right) const;
        TimeUnit operator -(const TimeUnit &right) const;
        TimeUnit operator *(const TimeUnit &right) const;
        TimeUnit operator /(const TimeUnit &right) const;

        TimeUnit operator %(const TimeUnit &right) const;

        // bit
        TimeUnit operator &(const TimeUnit &right) const;
        TimeUnit operator |(const TimeUnit &right) const;
        TimeUnit operator ^(const TimeUnit &right) const;
        TimeUnit operator <<(const TimeUnit &right) const;
        TimeUnit operator >>(const TimeUnit &right) const;

        // self math
        TimeUnit& operator +=(const TimeUnit &right);
        TimeUnit& operator -=(const TimeUnit &right);
        TimeUnit& operator *=(const TimeUnit &right);
        TimeUnit& operator /=(const TimeUnit &right);

        TimeUnit& operator %=(const TimeUnit &right);

        // self bit
        TimeUnit& operator &=(const TimeUnit &right);
        TimeUnit& operator |=(const TimeUnit &right);
        TimeUnit& operator ^=(const TimeUnit &right);
        TimeUnit& operator <<=(const TimeUnit &right);
        TimeUnit& operator >>=(const TimeUnit &right);

    private:
        TimeUnit(float seconds);

        Type mType;
        std::time_t mTime; // 2038
        Int64 mMicroseconds;
        long mSec;
        long mUSec;
    };

    TimeUnit operator "" _s(long double seconds);
    TimeUnit operator "" _ms(Uint64 milliseconds);
    TimeUnit operator "" _us(Uint64 microseconds);
}

#endif //OKHTTPFORK_TIMEUNIT_HPP
