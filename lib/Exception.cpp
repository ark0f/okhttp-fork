//
// Created by Good_Pudge.
//

#include "../include/Exception.hpp"

namespace ohf {
    Exception::Exception(Code code, const std::string &what) noexcept : m_code(code), m_what(what) {}

    Exception::Code Exception::code() const noexcept {
        return m_code;
    }

    std::string Exception::message() const noexcept {
        return m_what;
    }

    const char *Exception::what() const noexcept {
        return m_what.c_str();
    }

    std::ostream &operator<<(std::ostream &stream, const Exception &e) {
        stream << e.m_what;
        return stream;
    }
}