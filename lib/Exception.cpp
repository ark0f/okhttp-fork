//
// Created by Good_Pudge.
//

#include "../include/Exception.hpp"

using namespace ohf;

Exception::Exception(const int &code, const std::string &what) noexcept : m_code(code), m_what(what) {}

int Exception::code() const noexcept {
    return m_code;
}

const char *Exception::what() const noexcept {
    return m_what.c_str();
}