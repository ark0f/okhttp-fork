//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_OOREXCEPTION_HPP
#define OKHTTPFORK_OOREXCEPTION_HPP

#include <ohf/Config.hpp>
#include "Exception.hpp"

namespace ohf {
    class RangeException : public Exception {
    public:
        explicit RangeException(Int64 index);

        Int64 index() const noexcept;

    private:
        Int64 m_index;
    };
}

#endif // OKHTTPFORK_OOREXCEPTION_HPP
