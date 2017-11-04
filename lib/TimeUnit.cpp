//
// Created by Good_Pudge.
//

#include <ctime>
#include "../include/TimeUnit.hpp"


namespace ohf {
    const TimeUnit TimeUnit::ZERO = {0, Type::SECONDS};
    const TimeUnit TimeUnit::MINUS_ONE_SECOND = {-1, Type::SECONDS};

    TimeUnit::TimeUnit(Int64 count, const TimeUnit::Type &type) :
            mSec(count / static_cast<int>(type)),
            mUSec(count % static_cast<int>(type)),
            mMicroseconds(count),
            time(count / static_cast<int>(type))
    {}

    TimeUnit TimeUnit::seconds(float time) {
        return {static_cast<Int64>(time * static_cast<int>(Type::MICROSECONDS)), TimeUnit::Type::MICROSECONDS};
    }

    TimeUnit TimeUnit::milliseconds(int time) {
        return {time, TimeUnit::Type::MILLISECONDS};
    }

    TimeUnit TimeUnit::microseconds(long long int time) {
        return {time, TimeUnit::Type::MICROSECONDS};
    }

    std::time_t TimeUnit::std_time() const {
        return time;
    }

    float TimeUnit::seconds() const {
        return mMicroseconds / static_cast<int>(Type::SECONDS)
             + mMicroseconds % static_cast<int>(Type::SECONDS);
    }

    Int32 TimeUnit::milliseconds() const {
        return mMicroseconds / static_cast<int>(Type::MILLISECONDS);
    }

    Int64 TimeUnit::microseconds() const {
        return mMicroseconds;
    }

    long TimeUnit::sec() const {
        return mSec;
    }

    long TimeUnit::usec() const {
        return mUSec;
    }

    bool TimeUnit::operator==(const TimeUnit &right) const {
        return mMicroseconds == right.mMicroseconds;
    }

    bool TimeUnit::operator!=(const TimeUnit &right) const {
        return mMicroseconds != right.mMicroseconds;
    }

    bool TimeUnit::operator>=(const TimeUnit &right) const {
        return mMicroseconds >= right.mMicroseconds;
    }

    bool TimeUnit::operator<=(const TimeUnit &right) const {
        return mMicroseconds <= right.mMicroseconds;
    }

    bool TimeUnit::operator>(const TimeUnit &right) const {
        return mMicroseconds > right.mMicroseconds;
    }

    bool TimeUnit::operator<(const TimeUnit &right) const {
        return mMicroseconds < right.mMicroseconds;
    }

    TimeUnit TimeUnit::operator+(const TimeUnit &right) const {
        return {mMicroseconds + right.mMicroseconds, TimeUnit::Type::MICROSECONDS};
    }

    TimeUnit TimeUnit::operator-(const TimeUnit &right) const {
        return {mMicroseconds - right.mMicroseconds, TimeUnit::Type::MICROSECONDS};
    }

    TimeUnit TimeUnit::operator*(const TimeUnit &right) const {
        return {mMicroseconds * right.mMicroseconds, TimeUnit::Type::MICROSECONDS};
    }

    TimeUnit TimeUnit::operator/(const TimeUnit &right) const {
        return {mMicroseconds * right.mMicroseconds, TimeUnit::Type::MICROSECONDS};
    }

    TimeUnit TimeUnit::operator^(const TimeUnit &right) const {
        return {mMicroseconds ^ right.mMicroseconds, TimeUnit::Type::MICROSECONDS};
    }
}