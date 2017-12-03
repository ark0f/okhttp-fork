//
// Created by Good_Pudge.
//

#include <ohf/HttpURL.hpp>
#include <ohf/Cookie.hpp>
#include <iostream>
#include <ohf/Exception.hpp>

int main() {
    try {
        ohf::HttpURL url = "https://www.google.com/";

        ohf::Cookie one_cookie = ohf::Cookie::Builder()
                .hostOnlyDomain(".github.com")
                .expiresAt(ohf::TimeUnit::seconds(10))
                .secure()
                .httpOnly()
                .name("Hello")
                .value("World")
                .path("/some/path")
                .build();

        std::cout << one_cookie.name() << " = " << one_cookie.value() << std::endl
                  << "Domain:           " << one_cookie.domain() << std::endl
                  << "Expires at:       " << one_cookie.expiresAt().seconds() << std::endl
                  << "Host only:        " << one_cookie.hostOnly() << std::endl
                  << "HTTP only:        " << one_cookie.httpOnly() << std::endl
                  << "Path:             " << one_cookie.path() << std::endl
                  << "Persistent:       " << one_cookie.persistent() << std::endl
                  << "Secure:           " << one_cookie.secure() << std::endl
                  << "URL match Cookie: " << one_cookie.matches(url) << std::endl;

        ohf::Headers headers = ohf::Headers::Builder()
                .add("Set-Cookie", "Hello=world")
                .add("Set-Cookie", "Yes=No; Max-Age=123")
                .build();

        std::vector<ohf::Cookie> cookies = ohf::Cookie::parseAll(url, headers);
        for (auto &cookie : cookies) {
            std::cout << cookie.name() << " = " << cookie.value() << std::endl
                      << "Domain:           " << one_cookie.domain() << std::endl
                      << "Expires at:       " << one_cookie.expiresAt().seconds() << std::endl
                      << "Host only:        " << one_cookie.hostOnly() << std::endl
                      << "HTTP only:        " << one_cookie.httpOnly() << std::endl
                      << "Path:             " << one_cookie.path() << std::endl
                      << "Persistent:       " << one_cookie.persistent() << std::endl
                      << "Secure:           " << one_cookie.secure() << std::endl
                      << "URL match Cookie: " << one_cookie.matches(url) << std::endl;
        }
    } catch (ohf::Exception &e) {
        std::cout << e.what() << std::endl << "\tCode: " << e.code() << std::endl;
        return 1;
    }

    return 0;
}