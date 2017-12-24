//
// Created by Good_Pudge.
//

#include <ohf/Exception.hpp>

namespace ohf {
    Exception *Exception::m_last = nullptr;

    Exception::Exception(const Code &code, const std::string &what) noexcept : m_code(code), m_what(what) {
        m_last = this;
    }

    Exception::Code Exception::code() const noexcept {
        return m_code;
    }

    std::string Exception::message() const noexcept {
        return m_what;
    }

    const char *Exception::what() const noexcept {
        return m_what.c_str();
    }

    const Exception* Exception::last() noexcept {
        return m_last;
    }
}