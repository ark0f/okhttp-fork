//
// Created by Good_Pudge.
//

#include "../include/Cookie.hpp"

namespace ohf {
    Cookie Cookie::Builder::build() {
        Cookie cookie;
        cookie.m_expiresAt = m_expiresAt;
        cookie.m_hostOnly = m_hostOnly;
        cookie.m_httpOnly = m_httpOnly;
        cookie.m_secure = m_secure;
        cookie.m_persistent = m_persistent;
        cookie.m_name = m_name;
        cookie.m_value = m_value;
        cookie.m_path = m_path;
        cookie.m_domain = m_domain;
        return cookie;
    }

    void Cookie::Builder::domain(const std::string &domain) {
        m_domain = domain;
    }

    void Cookie::Builder::expiresAt(time_t expiresAt) {
        m_expiresAt = expiresAt;
    }

    void Cookie::Builder::hostOnlyDomain(const std::string &domain) {
        m_domain = domain;
        m_httpOnly = true;
    }

    void Cookie::Builder::httpOnly() {
        m_httpOnly = true;
    }

    void Cookie::Builder::name(const std::string &name) {
        m_name = name;
    }

    void Cookie::Builder::path(const std::string &path) {
        m_path = path;
    }

    void Cookie::Builder::secure() {
        m_secure = true;
    }

    void Cookie::Builder::value(const std::string &value) {
        m_value = value;
    }
}