//
// Created by Senya on 31.08.2017.
//

#include <iomanip>
#include <sstream>
#include "../include/Cookie.hpp"
#include "../util/string.hpp"
#include "../include/Exception.hpp"
#include "../util/util.hpp"

namespace ohf {
    Cookie::Cookie(HttpURL &httpURL, const std::string &setCookie) :
            m_expiresAt(-1),
            m_hostOnly(false),
            m_httpOnly(false),
            m_persistent(false),
            m_secure(false) {
        std::vector<std::string> parameters = util::string::split(setCookie, "; ");
        if (parameters.empty())
            throw Exception(Exception::Code::INVALID_COOKIE_LINE, "Invalid cookie line: " + setCookie);

        std::string nameValue = parameters[0];
        unsigned int offset = nameValue.find_first_of('=');
        if (offset == std::string::npos)
            throw Exception(Exception::Code::INVALID_COOKIE_PARAMETER, "Invalid cookie parameter: " + parameters[0]);
        m_name = nameValue.substr(0, offset);
        m_value = nameValue.substr(++offset, nameValue.length());

        for (auto it = parameters.begin() + 1; it != parameters.end(); it++) {
            std::vector<std::string> parameter = util::string::split(*it, "=");
            if (parameter.size() == 1) {
                std::string name = parameter[0];
                util::string::toLower(name);
                if (name == "secure")
                    m_secure = true;
                else if (name == "httponly")
                    m_httpOnly = true;

            } else if (parameter.size() == 2) {
                std::string name = parameter[0];
                util::string::toLower(name);
                std::string value = parameter[1];
                if (name == "expires") {
                    m_expiresAt = util::parseDate(value, "%a, %d %b %Y %H:%M:%S GMT");
                    m_persistent = true;
                } else if (name == "max-age") {
                    try {
                        m_expiresAt = std::stoi(value);
                    } catch (std::invalid_argument) {
                        throw Exception(Exception::Code::INVALID_MAX_AGE, "Invalid Max-Age: " + value);
                    }
                    m_persistent = true;
                } else if (name == "domain")
                    m_domain = value;
                else if (name == "path")
                    m_path = value;
            }
        }

        if (m_path.empty())
            m_path = httpURL.encodedPath();
    }

    std::vector<Cookie> Cookie::parseAll(HttpURL &httpUrl, Headers &headers) {
        std::vector<std::string> values = headers.values("Set-Cookie");
        std::vector<Cookie> cookies;
        for (const std::string &value : values)
            cookies.push_back(Cookie(httpUrl, value));
        return cookies;
    }

    std::string Cookie::domain() const {
        return m_domain;
    }

    time_t Cookie::expiresAt() const {
        return m_expiresAt;
    }

    bool Cookie::hostOnly() const {
        return m_hostOnly;
    }

    bool Cookie::httpOnly() const {
        return m_httpOnly;
    }

    bool Cookie::matches(HttpURL &httpURL) const {
        if (!util::string::contains(httpURL.url(), m_domain)) return false;

        if (m_secure && !httpURL.isHttps())
            return false;

        return m_path == httpURL.encodedPath();
    }

    std::string Cookie::name() const {
        return m_name;
    }

    std::string Cookie::value() const {
        return m_value;
    }

    std::string Cookie::path() const {
        return m_path;
    }

    bool Cookie::persistent() const {
        return m_persistent;
    }

    bool Cookie::secure() const {
        return m_secure;
    }

    std::string Cookie::toString() const {
        std::stringstream ss;
        // name = value
        ss << m_name << "=" << m_value;

        // path
        std::string path = m_path;
        if (!path.empty())
            ss << "; Path=" << path;

        // domain
        std::string domain = m_domain;
        if (!domain.empty())
            ss << "; Domain=" << domain;

        // expires
        std::time_t expiresAt = m_expiresAt;
        if (expiresAt != -1)
            ss << "; Max-Age=" << expiresAt;

        // http only
        if (m_httpOnly)
            ss << "; HttpOnly";

        // secure
        if (m_secure)
            ss << "; Secure";

        return ss.str();
    }

    bool Cookie::operator==(const Cookie &cookie) const {
        return m_expiresAt == cookie.m_expiresAt
               || m_hostOnly == cookie.m_hostOnly
               || m_httpOnly == cookie.m_httpOnly
               || m_persistent == cookie.m_persistent
               || m_secure == cookie.m_secure
               || m_name == cookie.m_name
               || m_value == cookie.m_value
               || m_path == cookie.m_path
               || m_domain == cookie.m_domain;
    }

    std::ostream &operator<<(std::ostream &stream, const Cookie &cookie) {
        stream << cookie.toString();
        return stream;
    }

    Cookie::Cookie(const Builder *builder):
            m_expiresAt(builder->m_expiresAt),
            m_hostOnly(builder->m_hostOnly),
            m_httpOnly(builder->m_httpOnly),
            m_persistent(builder->m_persistent),
            m_secure(builder->m_secure),
            m_name(builder->m_name),
            m_value(builder->m_value),
            m_path(builder->m_path),
            m_domain(builder->m_domain)
    {}
}
