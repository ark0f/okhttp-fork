//
// Created by Senya on 31.08.2017.
//

#ifndef OKHTTPFORK_COOKIE_HPP
#define OKHTTPFORK_COOKIE_HPP

#include "HttpURL.hpp"
#include "Headers.hpp"

namespace ohf {
    class Cookie {
    public:
        class Builder {
        public:
            Builder();

            Cookie build();

            Builder &name(const std::string &name);

            Builder &value(const std::string &value);

            Builder &path(const std::string &path);

            Builder &domain(const std::string &domain);

            Builder &hostOnlyDomain(const std::string &domain);

            Builder &expiresAt(const TimeUnit &expiresAt);

            Builder &httpOnly();

            Builder &secure();

        private:
            TimeUnit m_expiresAt;
            bool
                    m_hostOnly,
                    m_httpOnly,
                    m_secure,
                    m_persistent;
            std::string
                    m_name,
                    m_value,
                    m_path,
                    m_domain;

            friend class ohf::Cookie;
        };

        Cookie(HttpURL &httpURL, const std::string &setCookie);

        static std::vector<Cookie> parseAll(HttpURL &httpUrl, Headers &headers);

        TimeUnit expiresAt() const;

        bool hostOnly() const;

        bool httpOnly() const;

        bool persistent() const;

        bool secure() const;

        bool matches(HttpURL &httpURL) const;

        std::string name() const;

        std::string value() const;

        std::string path() const;

        std::string domain() const;

        std::string toString() const;

        bool operator==(const Cookie &cookie) const;

        friend std::ostream &operator<<(std::ostream &stream, const Cookie &cookie);

    private:
        Cookie(const Builder *builder);

        TimeUnit m_expiresAt;
        bool
                m_hostOnly,
                m_httpOnly,
                m_persistent,
                m_secure;
        std::string
                m_name,
                m_value,
                m_path,
                m_domain;
    };
}

#endif //OKHTTPFORK_COOKIE_HPP
