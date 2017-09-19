//
// Created by Good_Pudge.
//

#include <iostream>
#include "../include/Exception.hpp"
#include "../include/Cookie.hpp"
#include "../include/HttpURL.hpp"

int main() {
    try {
        ohf::HttpURL url = "https://www.google.com/";

        ohf::Cookie::Builder builder;
        builder.hostOnlyDomain(".github.com");
        builder.expiresAt(123);
        builder.secure();
        builder.httpOnly();
        builder.name("Hello");
        builder.value("World");
        builder.path("/q=123");
        ohf::Cookie one_cookie = builder.build();

        std::cout << one_cookie.name() << " = " << one_cookie.value() << std::endl;
        std::cout << "Domain:     " << one_cookie.domain() << std::endl;
        std::cout << "Expires at: " << one_cookie.expiresAt() << std::endl;
        std::cout << "Host only:  " << one_cookie.hostOnly() << std::endl;
        std::cout << "HTTP only:  " << one_cookie.httpOnly() << std::endl;
        std::cout << "Path:       " << one_cookie.path() << std::endl;
        std::cout << "Persistent: " << one_cookie.persistent() << std::endl;
        std::cout << "Secure:     " << one_cookie.secure() << std::endl;
        std::cout << "Stream:     " << one_cookie << std::endl;
        std::cout << "URL match Cookie: " << one_cookie.matches(url) << std::endl;

        ohf::Headers::Builder headersBuilder;
        headersBuilder.add("Set-Cookie", "Hello=world");
        headersBuilder.add("Set-Cookie", "Yes=No; Max-Age=123");
        ohf::Headers headers = headersBuilder.build();
        std::vector<ohf::Cookie> cookies = ohf::Cookie::parseAll(url, headers);
        for (auto &cookie : cookies) {
            std::cout << cookie.name() << " = " << cookie.value() << std::endl;
            std::cout << "Domain:     " << cookie.domain() << std::endl;
            std::cout << "Expires at: " << cookie.expiresAt() << std::endl;
            std::cout << "Host only:  " << cookie.hostOnly() << std::endl;
            std::cout << "HTTP only:  " << cookie.httpOnly() << std::endl;
            std::cout << "Path:       " << cookie.path() << std::endl;
            std::cout << "Persistent: " << cookie.persistent() << std::endl;
            std::cout << "Secure:     " << cookie.secure() << std::endl;
            std::cout << "Stream:     " << cookie << std::endl;
            std::cout << "URL match Cookie: " << cookie.matches(url) << std::endl;
        }

    } catch (ohf::Exception &e) {
        std::cout << e.what() << std::endl << "\tCode: " << e.code() << std::endl;
        return 1;
    }

    return 0;
}