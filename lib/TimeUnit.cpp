//
// Created by Good_Pudge.
//

#include "../include/TimeUnit.hpp"

namespace ohf {
    const TimeUnit TimeUnit::ZERO = {0, Type::SECONDS};
    const TimeUnit TimeUnit::MINUS_ONE_SECOND = {-1, Type::SECONDS};

    TimeUnit::TimeUnit(Int64 count, const TimeUnit::Type &type) : mType(type) {
        Int32 multiplier, delimiter;
        switch (type) {
            case Type::SECONDS:
                multiplier = 1000000;
                delimiter = 1;
                break;
            case Type::MILLISECONDS:
                multiplier = delimiter = 1000;
                break;
            case Type::MICROSECONDS:
                multiplier = 1;
                delimiter = 1000000;
                break;
        }

        mMicroseconds = count * multiplier;
        mSec = count / delimiter;
        mUSec = count % delimiter;
        mTime = count / delimiter;
    }

    TimeUnit::TimeUnit(float seconds) {
        mMicroseconds = seconds * 1000000;
        mSec = static_cast<long>(seconds);
        mUSec = mMicroseconds % 1000000;
        mTime = static_cast<std::time_t>(seconds);
        mType = Type::SECONDS;
    }

    TimeUnit TimeUnit::seconds(float time) {
        return {time};
    }

    TimeUnit TimeUnit::milliseconds(Int32 time) {
        return {time, Type::MILLISECONDS};
    }

    TimeUnit TimeUnit::microseconds(Int64 time) {
        return {time, Type::MICROSECONDS};
    }

    std::time_t TimeUnit::std_time() const {
        return mTime;
    }

    float TimeUnit::seconds() const {
        return mMicroseconds / 1000000.0f;
    }

    Int32 TimeUnit::milliseconds() const {
        return mMicroseconds / 1000;
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

    Int64 TimeUnit::value() const {
        Int32 delimiter;
        switch (mType) {
            case Type::SECONDS:
                delimiter = 1000000;
                break;
            case Type::MILLISECONDS:
                delimiter = 1000;
                break;
            case Type::MICROSECONDS:
                delimiter = 1;
                break;
        }
        return mMicroseconds / delimiter;
    }

    std::string TimeUnit::toString() const {
        std::string str = std::to_string(value());
        switch(mType) {
            case Type::SECONDS:
                str += " seconds";
                break;
            case Type::MILLISECONDS:
                str += " milliseconds";
                break;
            case Type::MICROSECONDS:
                str += " microseconds";
                break;
        }
        return str;
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