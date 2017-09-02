//
// Created by Good_Pudge.
//

#include "../include/Exception.hpp"

using namespace ohf;

Exception::Exception(const int &code, const std::string &what) {
    this->code_ = code;
    this->what_ = what;
}

int Exception::code() {
    return code_;
}

std::string Exception::what() {
    return what_;
}