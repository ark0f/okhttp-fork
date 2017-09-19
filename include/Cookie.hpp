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
            Builder() : m_expiresAt(-1), m_hostOnly(false), m_httpOnly(false), m_secure(false), m_persistent(false) {};

            Cookie build();

            void name(const std::string &name);

            void value(const std::string &value);

            void path(const std::string &path);

            void domain(const std::string &domain);

            void hostOnlyDomain(const std::string &domain);

            void expiresAt(time_t expiresAt);

            void httpOnly();

            void secure();

            friend class Cookie;

        private:
            time_t m_expiresAt;
            bool m_hostOnly;
            bool m_httpOnly;
            bool m_secure;
            bool m_persistent;
            std::string m_name;
            std::string m_value;
            std::string m_path;
            std::string m_domain;
        };

        Cookie() = default;

        Cookie(HttpURL &httpURL, const std::string &setCookie);

        static std::vector<Cookie> parseAll(HttpURL &httpUrl, Headers &headers);

        time_t expiresAt();

        bool hostOnly();

        bool httpOnly();

        bool persistent();

        bool secure();

        bool matches(HttpURL &httpURL);

        std::string name();

        std::string value();

        std::string path();

        std::string domain();

        bool operator==(const Cookie &cookie);

        friend std::ostream &operator<<(std::ostream &stream, Cookie &cookie);

    private:
        time_t m_expiresAt;
        bool m_hostOnly;
        bool m_httpOnly;
        bool m_persistent;
        bool m_secure;
        std::string m_name;
        std::string m_value;
        std::string m_path;
        std::string m_domain;
    };
}

#endif //OKHTTPFORK_COOKIE_HPP
