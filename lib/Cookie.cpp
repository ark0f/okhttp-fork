//
// Created by Senya on 31.08.2017.
//

#include <iomanip>
#include <sstream>
#include "../include/Cookie.hpp"
#include "../util/string.hpp"
#include "../include/Exception.hpp"

namespace ohf {
    Cookie::Cookie(HttpURL &httpURL, const std::string &setCookie) :
            m_expiresAt(-1), m_hostOnly(false), m_httpOnly(false), m_persistent(false), m_secure(false) {
        std::vector<std::string> parameters = util::string::split(setCookie, "; ");
        if (parameters.empty())
            throw Exception(Exception::Code::INVALID_COOKIE_LINE, "Invalid cookie line: " + setCookie);

        std::vector<std::string> nameValue = util::string::split(parameters[0], "=");
        if (nameValue.size() != 2)
            throw Exception(Exception::Code::INVALID_COOKIE_PARAMETER, "Invalid cookie parameter: " + parameters[0]);
        m_name = nameValue[0];
        m_value = nameValue[1];

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
                    std::tm t{};
                    std::istringstream iss(value);
                    iss >> std::get_time(&t, "%a, %d %b %Y %H:%M:%S GMT");
                    m_expiresAt = std::mktime(&t);
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

    std::string Cookie::domain() {
        return m_domain;
    }

    bool Cookie::operator==(const Cookie &cookie) {
        return this == &cookie;
    }

    time_t Cookie::expiresAt() {
        return m_expiresAt;
    }

    bool Cookie::hostOnly() {
        return m_hostOnly;
    }

    bool Cookie::httpOnly() {
        return m_httpOnly;
    }

    bool Cookie::matches(HttpURL &httpURL) {
        if (!util::string::contains(httpURL.url(), m_domain)) return false;

        if (m_secure && !httpURL.isHttps())
            return false;

        return m_path == httpURL.encodedPath();
    }

    std::string Cookie::name() {
        return m_name;
    }

    std::string Cookie::path() {
        return m_path;
    }

    bool Cookie::persistent() {
        return m_persistent;
    }

    bool Cookie::secure() {
        return m_secure;
    }

    std::ostream &operator<<(std::ostream &stream, Cookie &cookie) {
        // name = value
        stream << "Set-Cookie: " << cookie.name() << "=" << cookie.value();

        // path
        std::string path = cookie.path();
        if (!path.empty())
            stream << "; " << "Path=" << path;

        // domain
        std::string domain = cookie.domain();
        if (!domain.empty())
            stream << "; " << "Domain=" << domain;

        // expires
        std::time_t expiresAt = cookie.expiresAt();
        if (expiresAt != -1)
            stream << "; Max-Age=" << expiresAt;

        // http only
        if (cookie.httpOnly())
            stream << "; HttpOnly";

        // secure
        if (cookie.secure())
            stream << "; Secure";

        return stream;
    }

    std::string Cookie::value() {
        return m_value;
    }
}
