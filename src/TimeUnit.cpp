//
// Created by Good_Pudge.
//

#include <ohf/TimeUnit.hpp>

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
        mSec = static_cast<long>(count / delimiter);
        mUSec = static_cast<long>(count % delimiter);
        mTime = count / delimiter;
    }

    TimeUnit::TimeUnit(float seconds) : mType(Type::SECONDS) {
        mMicroseconds = static_cast<Int64>(seconds * 1000000);
        mSec = static_cast<long>(seconds);
        mUSec = static_cast<long>(mMicroseconds % 1000000);
        mTime = static_cast<std::time_t>(seconds);
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
        return static_cast<Int32>(mMicroseconds / 1000);
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

    TimeUnit::Type TimeUnit::type() const {
        return mType;
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

    float TimeUnit::floatValue() const {
        float delimiter;
        switch (mType) {
            case Type::SECONDS:
                delimiter = 1000000.0f;
                break;
            case Type::MILLISECONDS:
                delimiter = 1000.0f;
                break;
            case Type::MICROSECONDS:
                delimiter = 1.0f;
                break;
        }
        return mMicroseconds / delimiter;
    }

    bool TimeUnit::operator ==(const TimeUnit &right) const {
        return mMicroseconds == right.mMicroseconds;
    }

    bool TimeUnit::operator !=(const TimeUnit &right) const {
        return mMicroseconds != right.mMicroseconds;
    }

    bool TimeUnit::operator >=(const TimeUnit &right) const {
        return mMicroseconds >= right.mMicroseconds;
    }

    bool TimeUnit::operator <=(const TimeUnit &right) const {
        return mMicroseconds <= right.mMicroseconds;
    }

    bool TimeUnit::operator >(const TimeUnit &right) const {
        return mMicroseconds > right.mMicroseconds;
    }

    bool TimeUnit::operator <(const TimeUnit &right) const {
        return mMicroseconds < right.mMicroseconds;
    }

    TimeUnit TimeUnit::operator +(const TimeUnit &right) const {
        return {mMicroseconds + right.mMicroseconds, TimeUnit::Type::MICROSECONDS};
    }

    TimeUnit TimeUnit::operator -(const TimeUnit &right) const {
        return {mMicroseconds - right.mMicroseconds, TimeUnit::Type::MICROSECONDS};
    }

    TimeUnit TimeUnit::operator *(const TimeUnit &right) const {
        return {mMicroseconds * right.mMicroseconds, TimeUnit::Type::MICROSECONDS};
    }

    TimeUnit TimeUnit::operator /(const TimeUnit &right) const {
        return {mMicroseconds / right.mMicroseconds, TimeUnit::Type::MICROSECONDS};
    }

    TimeUnit TimeUnit::operator %(const TimeUnit &right) const {
        return {mMicroseconds % right.mMicroseconds, TimeUnit::Type::MICROSECONDS};
    }

    TimeUnit TimeUnit::operator &(const TimeUnit &right) const {
        return {mMicroseconds & right.mMicroseconds, TimeUnit::Type::MICROSECONDS};
    }

    TimeUnit TimeUnit::operator |(const TimeUnit &right) const {
        return {mMicroseconds | right.mMicroseconds, TimeUnit::Type::MICROSECONDS};
    }

    TimeUnit TimeUnit::operator ^(const TimeUnit &right) const {
        return {mMicroseconds ^ right.mMicroseconds, TimeUnit::Type::MICROSECONDS};
    }

    TimeUnit TimeUnit::operator <<(const TimeUnit &right) const {
        return {mMicroseconds << right.mMicroseconds, TimeUnit::Type::MICROSECONDS};
    }

    TimeUnit TimeUnit::operator >>(const TimeUnit &right) const {
        return {mMicroseconds >> right.mMicroseconds, TimeUnit::Type::MICROSECONDS};
    }

    TimeUnit& TimeUnit::operator +=(const TimeUnit &right) {
        mMicroseconds += right.mMicroseconds;
        return *this;
    }

    TimeUnit& TimeUnit::operator -=(const TimeUnit &right) {
        mMicroseconds -= right.mMicroseconds;
        return *this;
    }

    TimeUnit& TimeUnit::operator *=(const TimeUnit &right) {
        mMicroseconds *= right.mMicroseconds;
        return *this;
    }

    TimeUnit& TimeUnit::operator /=(const TimeUnit &right) {
        mMicroseconds /= right.mMicroseconds;
        return *this;
    }

    TimeUnit& TimeUnit::operator %=(const TimeUnit &right) {
        mMicroseconds %= right.mMicroseconds;
        return *this;
    }

    TimeUnit& TimeUnit::operator &=(const TimeUnit &right) {
        mMicroseconds &= right.mMicroseconds;
        return *this;
    }

    TimeUnit& TimeUnit::operator |=(const TimeUnit &right) {
        mMicroseconds |= right.mMicroseconds;
        return *this;
    }

    TimeUnit& TimeUnit::operator ^=(const TimeUnit &right) {
        mMicroseconds ^= right.mMicroseconds;
        return *this;
    }

    TimeUnit& TimeUnit::operator <<=(const TimeUnit &right) {
        mMicroseconds <<= right.mMicroseconds;
        return *this;
    }

    TimeUnit& TimeUnit::operator >>=(const TimeUnit &right) {
        mMicroseconds >>= right.mMicroseconds;
        return *this;
    }

    TimeUnit operator "" _s(long double seconds) {
        return TimeUnit::seconds(static_cast<float>(seconds));
    }

    TimeUnit operator "" _ms(Uint64 milliseconds) {
        return TimeUnit::milliseconds(static_cast<Int32>(milliseconds));
    }

    TimeUnit operator "" _us(Uint64 microseconds) {
        return TimeUnit::microseconds(static_cast<Int64>(microseconds));
    }
}