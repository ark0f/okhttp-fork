//
// Created by Good_Pudge.
//

#include <ohf/RangeException.hpp>

namespace ohf {
    RangeException::RangeException(Int64 index) :
            m_index(index),
            Exception(Exception::Code::OUT_OF_RANGE, "Out of range: " + std::to_string(index)) {}

    Int64 RangeException::index() const noexcept {
        return m_index;
    }
}